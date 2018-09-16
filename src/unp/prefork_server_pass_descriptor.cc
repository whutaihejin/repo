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

struct ChildInfo {
    pid_t child_pid; // process ID
    int child_pipefd; // parent's stream pipe to/from child
    int child_status; // 0 means ready and 1 means busy
    long child_count; // connections handled
};

// void (*signal(int signo, void(*func)(int)))(int);
typedef void signal_hanlder_t(int);
signal_hanlder_t* signal(int signo, signal_hanlder_t* func);

// signal SIGCHLD handler
void signal_child_handler(int signo);
void signal_interrupt_handler(int signo);

// echo what readed from the client
void WebImpl(int fd);

pid_t MakeChild(int, int, ChildInfo*);

void ChildMain(int);

int WriteDescriptor(int fd, void* ptr, size_t nbytes, int sendfd);
int ReadDescriptor(int fd, void* ptr, size_t nbytes, int* recvfd);

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

    fd_set rset, master_set;
    int max_fd = listen_fd;
    int available_count = FLAGS_child_num;
    int select_count = 0;

    // set listen fd to select
    FD_SET(listen_fd, &master_set);
    
    ChildInfo* child_list = new ChildInfo[FLAGS_child_num];
    for (int i = 0; i < FLAGS_child_num; ++i) {
        MakeChild(i, listen_fd, child_list);
        FD_SET(child_list[i].child_pipefd, &master_set);
        max_fd = std::max(max_fd, child_list[i].child_pipefd);
    }
   
    // set signal handler
    signal(SIGCHLD, signal_child_handler);
    signal(SIGINT, signal_interrupt_handler);

    // flow control
    char c = 'a'; // dummy char
    for (;;) {
        rset = master_set;
        if (available_count <= 0) {
            FD_CLR(listen_fd, &rset);
        }
        select_count = select(max_fd + 1, &rset, NULL, NULL, NULL);

        // accept new connection
        if (FD_ISSET(listen_fd, &rset)) {
            int conn_fd = accept(listen_fd, NULL, NULL);
            int index = 0;
            for (index = 0; index < FLAGS_child_num; ++index) {
                if (child_list[index].child_status == 0) {
                    break;
                }
            }
            if (index == FLAGS_child_num) {
                printf("no available chlild work process\n");
            }
            child_list[index].child_status = 1;
            child_list[index].child_count += 1;
            available_count--;

            WriteDescriptor(child_list[index].child_pipefd, &c, 1, conn_fd);
            close(conn_fd);
            if (--select_count == 0) {
                continue;
            }
        }
        for (int i = 0; i < FLAGS_child_num; ++i) {
            if (FD_ISSET(child_list[i].child_pipefd, &rset)) {
                if (read(child_list[i].child_pipefd, &c, 1) == 0) {
                    printf("child %d terminated unexpectedly\n", i);
                    continue;
                }
                child_list[i].child_status = 0;
                available_count++;
                if (--select_count == 0) {
                    break;
                }
            }
        }
    }

    delete[] child_list;
    // how to exit gracefully?
    return 0;
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

pid_t MakeChild(int i, int listen_fd, ChildInfo* child_list) {
    int sockfd[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);
    pid_t pid = 0;
    if ((pid = fork()) > 0) {
        close(sockfd[1]);
        ChildInfo& info = child_list[i];
        info.child_pid = pid;
        info.child_pipefd = sockfd[0];
        info.child_status = 0;
        return pid;
    }
    dup2(sockfd[1], STDERR_FILENO);
    close(sockfd[0]);
    close(sockfd[1]);
    close(listen_fd);
    ChildMain(i);
    return static_cast<pid_t>(0);
}

void ChildMain(int i) {
    std::cout << (i + 1) << "th child begin with pid " << getpid() << std::endl;
    socklen_t sock_len = 0;
    struct sockaddr_in cli_addr;
    for (;;) {
        int n = 0, conn_fd = -1;
        char c = 'a';
        if ((n = ReadDescriptor(STDERR_FILENO, &c, 1, &conn_fd)) == 0) {
            std::cout << "can't read descriptor" << std::endl;
            continue;
        }
        if (conn_fd < 0) {
            std::cout << "invalid descriptor " << conn_fd << std::endl;
            continue;
        }
        getpeername(conn_fd,(struct sockaddr*)&cli_addr, &sock_len);
        // remote end-point info
        EndPoint remote(&cli_addr);
        std::cout << (i + 1) << "th child accept " << remote.Text() << std::endl;

        WebImpl(conn_fd);
        close(conn_fd);
        // tell parent we're ready again
        write(STDERR_FILENO, &c, 1);
    }
}

int ReadDescriptor(int fd, void* ptr, size_t nbytes, int* recvfd) {
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct msghdr msg;
    struct iovec iov[1];
    // build msg
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    // build iovec
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    // read msg
    int n = 0; // for count
    if ((n = recvmsg(fd, &msg, 0)) <= 0) {
        return n;
    }
    struct cmsghdr* cmptr = NULL;
    if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL && cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmptr->cmsg_level != SOL_SOCKET) {
            std::cout << "control level not equal SOL_SOCKET" << std::endl;
        }
        if (cmptr->cmsg_type != SCM_RIGHTS) {
            std::cout << "control type not equal SCM_RIGHTS" << std::endl;
        }
        *recvfd = *((int *) CMSG_DATA(cmptr));
    } else {
        *recvfd = -1;
    }
    return n;
}

int WriteDescriptor(int fd, void* ptr, size_t nbytes, int sendfd) {
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct msghdr msg;
    struct iovec iov[1];
    // build msg
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    
    struct cmsghdr* cmptr = CMSG_FIRSTHDR(&msg);
    cmptr->cmsg_len = CMSG_LEN(sizeof(int));
    cmptr->cmsg_level = SOL_SOCKET; 
    cmptr->cmsg_type = SCM_RIGHTS; 
    *((int *) CMSG_DATA(cmptr)) = sendfd;
    
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    // build iovec
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    return sendmsg(fd, &msg, 0);
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
