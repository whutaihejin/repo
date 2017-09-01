#include <stdio.h>
#include <unistd.h>  // for write & close
#include <time.h> // for time & ctime
#include <string.h> // for memset
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_LISTEN_QUEUE 100

int main(int argc, char* argv[]) {
    char buffer[MAX_BUFFER_SIZE] = {0};

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    listen(listen_fd, MAX_LISTEN_QUEUE);

    for (;;) {
        int connect_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
        time_t ticks = time(NULL);
        snprintf(buffer, MAX_BUFFER_SIZE, "%.24s\r\n", ctime(&ticks));
        write(connect_fd, buffer, strlen(buffer));
        close(connect_fd);
    }
    return 0;
}
