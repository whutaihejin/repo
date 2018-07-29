#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 8017
#define BACKLOG 1024
#define BUFSIZE 1024

#define ERROR_LOG(prefix, code) \
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

// echo what readed from the client
void EchoImpl(int fd);

// 信号注册函数
// void (*signal(int signo, void(*func)(int)))(int);
typedef void signal_hanlder_t(int);
signal_hanlder_t* signal(int signo, signal_hanlder_t* func);

// signal SIGCHLD handler
void signal_child_handler(int signo) {
    pid_t pid = 0;
    int status = 0;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        std::cout << "receive signo " << signo << " child " << pid << " terminated with status " << status << std::endl;
    }
    return;
}

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        ERROR_LOG("socket error", errno);
        return -1;
    }

    struct sockaddr_in serv_addr, cli_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    if (bind(listen_fd, (struct sockaddr*)(&serv_addr), sizeof(serv_addr)) != 0) {
        ERROR_LOG("bind error", errno);
        return -1;
    }

    if (listen(listen_fd, BACKLOG) != 0) {
        ERROR_LOG("listen error", errno);
        return -1;
    }
    signal(SIGCHLD, signal_child_handler);

    for (;;) {
        socklen_t len = sizeof(cli_addr);
        int conn_fd = accept(listen_fd, (struct sockaddr*)(&cli_addr), &len);
        if (conn_fd < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                ERROR_LOG("accept error", errno);
                break;
            }
        }
        // remote end-point info
        EndPoint remote(&cli_addr);
        std::cout << remote.Text() << std::endl;

        int pid = fork();
        if (pid == 0) { // child process
            close(listen_fd);
            EchoImpl(conn_fd);
            exit(0);
        } else if (pid < 0) {
            ERROR_LOG("fork error", errno);
            return -1;
        }
        // parent process
        close(conn_fd);
    }
    return 0;
}

void EchoImpl(int fd) {
    int len = 0;
    char buf[BUFSIZE];

    for (;;) {
        while ((len = read(fd, buf, BUFSIZE)) > 0) {
            buf[std::min(len, BUFSIZE - 1)] = '\0';
            fputs(buf, stdout);
            write(fd, buf, len);
        }
        if (len < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                ERROR_LOG("read error", errno);
            }
        } else if (len == 0) {
            // end of file
            std::cout << "read end-of-file" << std::endl;
            // break;
        }
        break;
    }
}

signal_hanlder_t* signal(int signo, signal_hanlder_t* func) {
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT; // SunOS 4.x
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART; // SVR4, 4.4BSD
#endif
    }
    if (sigaction(signo, &act, &oact) < 0) {
        return SIG_ERR;
    }
    return oact.sa_handler;
}
