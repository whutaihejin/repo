#include <iostream>
#include <gflags/gflags.h>

#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <sys/mman.h>

DEFINE_string(host, "0.0.0.0", "hostname or ip address");
DEFINE_int32(port, 8017, "port number");
DEFINE_int32(child_num, 6, "preforked child process number");

#define LOG(prefix, code) \
    do { std::cout << prefix << " code=" << code << " msg=" << strerror(code) << std::endl; } while(0)

struct EndPoint {
    EndPoint(struct sockaddr_in* addr) {
        if (addr) {
            inet_ntop(AF_INET, &addr->sin_addr, present_, sizeof(present_));
            snprintf(present_ + strlen(present_), 8, ":%d", ntohs(addr->sin_port));
        }
    }
    const char* Text() {
        return present_;
    }
    char present_[INET_ADDRSTRLEN + 8];
};

// void (*signal(int signo, void(*func)(int)))(int);
typedef void signal_hanlder_t(int);
signal_hanlder_t* signal(int signo, signal_hanlder_t* func);

// signal SIGCHLD handler
void signal_child_handler(int signo);
void signal_interrupt_handler(int signo);

// echo what readed from the client
void WebImpl(int fd);

pid_t MakeChild(int, int);

void ChildMain(int, int);

class ProcessLock {
public:
    ProcessLock(): fd_(-1), mutex_(NULL) {
        const char* pathname = "mmap_lock";
        if ((fd_ = open(pathname, O_RDWR | O_CREAT, 0644)) == -1) {
            printf("open error: %s\n", strerror(errno));
            fd_ = -1;
            return;
        }
        // truncate shared memory segment so it would contain pthread_mutex_t.
        if (ftruncate(fd_, sizeof(pthread_mutex_t)) != 0) {
            printf("ftruncate error: %s\n", strerror(errno));
            fd_ = -1;
            return;
        }
        mutex_ = (pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (mutex_ == MAP_FAILED) {
            printf("mmap error: %s\n", strerror(errno));
            mutex_ = NULL;
            return;
        }
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) != 0) {
            printf("setpshared error: %s\n", strerror(errno));
            return;
        }
        pthread_mutex_init(mutex_, &attr);
        //
        unlink(pathname);
        close(fd_);
    }

    void Lock() {
        if (mutex_ != NULL) {
            pthread_mutex_lock(mutex_);
        }
    }

    void Unlock() {
        if (mutex_ != NULL) {
            pthread_mutex_unlock(mutex_);
        }
    }

private:
    int fd_;
    pthread_mutex_t* mutex_;
};

static ProcessLock file_lock;

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    std::cout << "host: " << FLAGS_host 
        << "\nport: " << FLAGS_port << std::endl;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(FLAGS_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int listen_fd;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        LOG("socket error", errno);
        return -1;
    }
    if (bind(listen_fd, (const struct sockaddr*)(&addr), sizeof(struct sockaddr_in)) != 0) {
        LOG("bind error", errno);
        return -1;
    }
    if (listen(listen_fd, 1024) != 0) {
        LOG("listen error", errno);
        return -1;
    }

    signal(SIGCHLD, signal_child_handler);
    signal(SIGINT, signal_interrupt_handler);
    
    pid_t* pid_list = new pid_t[FLAGS_child_num];
    for (int i = 0; i < FLAGS_child_num; ++i) {
        pid_list[i] = MakeChild(i, listen_fd);
    }

    for (;;) {
        pause();
    }
    return 0;
}

void signal_child_handler(int signo) {
    pid_t pid = 0;
    int status = 0;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        std::cout << "receive signo " << signo << " child " << pid << " terminated with status " << status << std::endl;
    }
    return;
}
    
void signal_interrupt_handler(int /* signo */) {
    struct rusage parent, child;

    if (getrusage(RUSAGE_SELF, &parent) < 0) {
        LOG("getrusage error", errno);
    }
    if (getrusage(RUSAGE_CHILDREN, &child) < 0) {
        LOG("getrusage error", errno);
    }
    const double kScala = 1000000.0;
    double parent_user_time = parent.ru_utime.tv_sec + parent.ru_utime.tv_usec / kScala;
    double child_user_time = child.ru_utime.tv_sec + child.ru_utime.tv_usec / kScala;
    double parent_sys_time = parent.ru_stime.tv_sec + parent.ru_stime.tv_usec / kScala; 
    double child_sys_time = child.ru_stime.tv_sec + child.ru_stime.tv_usec / kScala;
    std::cout << "parent user time: " << parent_user_time
        << "\nchild user time: " << child_user_time
        << "\nparent sys time: " << parent_sys_time
        << "\nchild sys time: " << child_sys_time << std::endl;
    exit(0);
}

void WebImpl(int fd) {
    char recvbuf[64] = {0};
    char sendbuf[1024] = {0};
    memset(sendbuf, 'a', 1024);
    int n = 0, bytes = 0;
    if ((n = read(fd, recvbuf, 64)) > 0) {
        bytes = std::stol(recvbuf);
    }
    std::cout << "server write: " << bytes << " bytes" << std::endl;
    write(fd, "begin ", 7);
    int unit = std::min(1024, bytes), wn = 0;
    while (bytes > 0 && (wn = write(fd, sendbuf, unit)) > 0) {
        bytes -= wn;
        unit = std::min(bytes, unit);
    }
}

pid_t MakeChild(int i, int listen_fd) {
    pid_t pid;
    if ((pid = fork()) > 0) {
        return pid;
    }
    std::cout << (i + 1) << "th child begin with pid " << getpid() << std::endl;
    ChildMain(i, listen_fd);
    return static_cast<pid_t>(0);
}

void ChildMain(int i, int listen_fd) {
    struct sockaddr_in cli_addr;
    for (;;) {
        socklen_t len = sizeof(struct sockaddr_in);
        file_lock.Lock();
        int conn_fd = accept(listen_fd, (struct sockaddr*)(&cli_addr), &len);
        file_lock.Unlock();
        if (conn_fd < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                LOG("accept error", errno);
                break;
            }
        }
        // remote end-point info
        EndPoint remote(&cli_addr);
        std::cout << (i + 1) << "th child accept " << remote.Text() << std::endl;

        WebImpl(conn_fd);
        close(conn_fd);
    }
}

