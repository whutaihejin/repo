#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define SERV_PORT 8017
#define BUFSIZE 1024

#define ERROR_LOG(prefix, code) \
    do { std::cout << prefix << " code=" << code << " msg=" << strerror(code) << std::endl; } while(0)

void cli_echo(FILE* in_fd, int out_fd);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <ip>" << std::endl;
        return -1;
    }
    const int size = 1;
    int fd_arr[size] = {0};
    for (int i = 0; i < size; ++i) {
        fd_arr[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (fd_arr[i] == -1) {
            ERROR_LOG("socket error", errno);
            return -1;
        }

        struct sockaddr_in serv_addr; // , cli_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(SERV_PORT);
        if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) != 1) {
            ERROR_LOG("inet_pton error", errno);
            return -1;
        }
        socklen_t len = sizeof(serv_addr);
        if (connect(fd_arr[i], (const struct sockaddr*)(&serv_addr), len) != 0) {
            ERROR_LOG("connect error", errno);
            return -1;
        }
    }

    cli_echo(stdin, fd_arr[0]);
    return 0;
}

void cli_echo(FILE* in, int out) {
    int in_fd = fileno(in);
    char buf[BUFSIZE] = {0};
    
    fd_set read_set;
    FD_ZERO(&read_set);
    bool is_stdio_eof = false;

    for (;;) {
        if (!is_stdio_eof) {
            FD_SET(in_fd, &read_set);
        }
        FD_SET(out, &read_set);
        int max_fd = std::max(in_fd, out) + 1;
        select(max_fd, &read_set, NULL, NULL, NULL);
        
        // read from stdio
        if (FD_ISSET(in_fd, &read_set)) {
            // std::cout << "read from stdio" << std::endl;
            int len = 0;
            if ((len = read(in_fd, buf, BUFSIZE)) == 0) {
                is_stdio_eof = true;
                shutdown(out, SHUT_WR);
                // clear 'in_fd' from select read set
                FD_CLR(in_fd, &read_set);
                std::cerr << "read end-of-file from stdio" << std::endl;
            } else {
                write(out, buf, len);
            }
        }
        
        // read from socket
        if (FD_ISSET(out, &read_set)) {
            // std::cout << "read from socket" << std::endl;
            int len = 0;
            if ((len = read(out, buf, BUFSIZE)) < 0) {
                ERROR_LOG("read error", errno);
                break;
            } else if (len == 0) {
                // std::cerr << "read end-of-file" << std::endl;
                if (is_stdio_eof) {
                    std::cerr << "normal terminated" << std::endl;
                } else {
                    std::cerr << "server terminated prematurely" << std::endl;
                }
                break;
            }
            write(fileno(stdout), buf, len);
        }
    }
}
