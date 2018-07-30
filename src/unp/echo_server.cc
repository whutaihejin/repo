#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <limits.h>

#define SERV_PORT 8017
#define BACKLOG 1024
#define BUFSIZE 1024
#define NILFD -1

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

    int client_size = 0;
    struct pollfd client[OPEN_MAX];
    client[0].fd = listen_fd;
    client[0].events = POLLRDNORM;
    // client array and initialization
    for (int i = 1; i < FD_SETSIZE; ++i) {
        client[i].fd = NILFD;
    }
    char buf[BUFSIZE] = {0};

    for (;;) {
        std::cerr << "before poll" << std::endl;
        int ready_number = poll(client, client_size + 1, -1);
        std::cerr << "after poll " << ready_number << " ready" << std::endl;
        // Testing read event is ok
        if (client[0].revents & POLLRDNORM) {
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

            int index = 0;
            for (index = 1; index < OPEN_MAX; ++index) {
                if (client[index].fd == NILFD) {
                    break;
                }
            }
            if (index == OPEN_MAX) {
                std::cerr << "too many clients, abort" << std::endl;
                exit(0);
            }
            client[index].fd = conn_fd;
            client[index].events = POLLRDNORM;
            client_size = std::max(index, client_size);
            
            if (--ready_number <= 0) {
                continue;
            }
        }

        for (int i = 1; i <= client_size; ++i) {
            int fd = client[i].fd;
            if (fd != NILFD && (client[i].revents & (POLLRDNORM | POLLERR))) {
                int len = 0;
                if ((len = read(fd, buf, BUFSIZE)) < 0) {
                    if (errno != ECONNRESET) {
                        ERROR_LOG("read error", errno);
                    }
                    close(fd);
                    client[i].fd = NILFD;
                } else if (len == 0) {
                    close(fd);
                    client[i].fd = NILFD;
                    std::cout << "close fd: " << fd << std::endl;
                } else {
                    std::cerr << "read bytes of " << len << std::endl;
                    write(fd, buf, len);
                    write(fileno(stdout), buf, len);
                }
                if (--ready_number <= 0) {
                    break;
                }
            }
        }
    }
}
