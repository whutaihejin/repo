#include <stdio.h>
#include <errno.h> // for strerror
#include <stdlib.h> // for exit
#include <unistd.h>  // for write & close
#include <string.h> // for memset
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_LISTEN_QUEUE 100

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: argv[0] <ip_address> <port>\n"), exit(1);
    }

    int sock_fd = 0;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n"), exit(1);
    }
    // build sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        printf("inet_pton error\n"), exit(1);
    }

    // connect to the server
    if (connect(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("connect error: %s\n", strerror(errno)), exit(1);
    }

    int n = 0;
    char buffer[MAX_BUFFER_SIZE] = {0};
    while ((n = read(sock_fd, buffer, MAX_BUFFER_SIZE - 1)) > 0) {
        buffer[n] = 0;
        if (fputs(buffer, stdout) == EOF) {
            printf("fputs error\n"), exit(1);
        }
    }
    if (n < 0) {
        printf("read error\n"), exit(1);
    }
    return 0;
}
