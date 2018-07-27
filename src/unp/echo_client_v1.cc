#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
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
    if (connect(fd, (const struct sockaddr*)(&serv_addr), len) != 0) {
        ERROR_LOG("connect error", errno);
        return -1;
    }

    cli_echo(stdin, fd);
    return 0;
}

void cli_echo(FILE* in, int out) {
    char recvbuf[BUFSIZE] = {0};
    char sendbuf[BUFSIZE] = {0};

    int len = 0;
    while (fgets(sendbuf, BUFSIZE, in) != NULL) {
        write(out, sendbuf, strlen(sendbuf));
        if ((len = read(out, recvbuf, BUFSIZE)) < 0) {
            ERROR_LOG("read error", errno);
            break;
        } else if (len == 0) {
            std::cout << "read end-of-file" << std::endl;
            break;
        }
        // set the terminating null character ('\0')
        recvbuf[std::min(len, BUFSIZE - 1)] = '\0';
        fputs(recvbuf, stdout);
    }
}
