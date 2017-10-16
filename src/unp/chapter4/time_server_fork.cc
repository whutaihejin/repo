#include <stdio.h>
#include <errno.h>
#include <stdlib.h> // for exit
#include <unistd.h>  // for write & close
#include <time.h> // for time & ctime
#include <string.h> // for memset
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_LISTEN_QUEUE 100

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <listen_port>\n", argv[0]), exit(1);
    }
    char buffer[MAX_BUFFER_SIZE] = {0};

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("bind error: %s\n", strerror(errno)), exit(1);
    }

    if (listen(listen_fd, MAX_LISTEN_QUEUE) != 0) {
        printf("listen error: %s\n", strerror(errno)), exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = 0;
    pid_t pid;
    for (;;) {
        client_addr_len = sizeof(client_addr);
        int connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if ((pid = fork()) < 0) {
            printf("fork error: %s\n", strerror(errno));
        } else if (pid == 0) { // child 
            close(listen_fd);
            // sho information about client
            printf("request from %s port %d\n", inet_ntop(AF_INET, &client_addr.sin_addr, buffer, sizeof(buffer)), ntohs(client_addr.sin_port));
            // handle the request
            time_t ticks = time(NULL);
            snprintf(buffer, MAX_BUFFER_SIZE, "%.24s\r\n", ctime(&ticks));
            write(connect_fd, buffer, strlen(buffer));
            close(connect_fd);
            // sleep(5);
            exit(0);
        }
        // parent
        close(connect_fd);
    }
    return 0;
}
