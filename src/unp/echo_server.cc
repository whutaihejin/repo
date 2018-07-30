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
#define NIL_FD (-1)

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
    int max_fd = listen_fd, client_size = -1;
    // client array and initialization
    int client[FD_SETSIZE] = {0};
    for (int i = 0; i < FD_SETSIZE; ++i) {
        client[i] = NIL_FD;
    }
    fd_set read_set, all_set;
    FD_ZERO(&all_set);
    FD_SET(listen_fd, &all_set);

    char buf[BUFSIZE] = {0};

    for (;;) {
        read_set = all_set;
        int ready_number = select(max_fd + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(listen_fd, &read_set)) {
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
            for (index = 0; index < FD_SETSIZE; ++index) {
                if (client[index] == NIL_FD) {
                    client[index] = conn_fd;
                    break;
                }
            }
            if (index == FD_SETSIZE) {
                std::cerr << "too many clients, abort" << std::endl;
                exit(0);
            }
            FD_SET(conn_fd, &all_set);
            max_fd = std::max(max_fd, conn_fd);
            client_size = std::max(index, client_size);
            
            if (--ready_number <= 0) {
                continue;
            }
        }

        for (int i = 0; i <= client_size; ++i) {
            int fd = client[i];
            if (fd != NIL_FD && FD_ISSET(fd, &read_set)) {
                int len = 0;
                if ((len = read(fd, buf, BUFSIZE)) == 0) {
                    close(fd);
                    FD_CLR(fd, &all_set);
                    client[i] = NIL_FD;
                } else {
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
