#include <iostream>
#include <gflags/gflags.h>

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

DEFINE_string(host, "127.0.0.1", "hostname or ip address");
DEFINE_int32(port, 8017, "port number");

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

    struct sockaddr_in cli_addr;
    for (;;) {
        socklen_t len = sizeof(cli_addr);
        int conn_fd = accept(listen_fd, (struct sockaddr*)(&cli_addr), &len);
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
        std::cout << remote.Text() << std::endl;

        pid_t pid;
        if ((pid = fork()) == 0) { // child process
            close(listen_fd);
            WebImpl(conn_fd);
            exit(0);
        } else if (pid < 0) {
            LOG("fork error", errno);
            return -1;
        }
        // parent process
        close(conn_fd);
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
    
void signal_interrupt_handler(int signo) {
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
