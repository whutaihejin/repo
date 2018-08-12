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
#include <pthread.h>

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

struct ThreadArgs {
    int stdin_fd;
    int socket_fd;
};

void* CopyTo(void* args) {
    ThreadArgs* a = static_cast<ThreadArgs*>(args);
    char buf[BUFSIZE] = {0};
    int len = 0;
    while ((len = read(a->stdin_fd, buf, BUFSIZE)) > 0) {
        write(a->socket_fd, buf, len);
    }
    if (len == 0) {
        std::cerr << "read end-of-file from stdin" << std::endl;
    } else if (len < 0) {
        ERROR_LOG("read error from stdin", errno);
    }
    shutdown(a->socket_fd, SHUT_WR);
    return NULL;
}

void cli_echo(FILE* in, int out) {
    int in_fd = fileno(in);
    char buf[BUFSIZE] = {0};
    ThreadArgs args;
    args.stdin_fd = in_fd;
    args.socket_fd = out;

    pthread_t tid = 0;
    pthread_create(&tid, NULL, CopyTo, &args);
    
    int len = 0;
    while ((len = read(out, buf, BUFSIZE)) > 0) {
        write(fileno(stdout), buf, len);
    }
    if (len == 0) {
        std::cerr << "read end-of-file from socket" << std::endl;
    } else if (len < 0) {
        ERROR_LOG("read error from socket", errno);
    }
}
