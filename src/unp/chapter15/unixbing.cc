#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/un.h> // sockaddr_un
#include <sys/socket.h> // socket
#include <unistd.h> // unlink
#include <string.h> // memset

int main(int argc, char* argv[]) {
    struct sockaddr_un addr1, addr2;
    if (argc != 2) {
        printf("usage: %s <path>", argv[0]), exit(1);
    }
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

    // remove file if exit and ignore error
    unlink(argv[1]);

    // init sockaddr_un
    memset(&addr1, 0, sizeof(addr1));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
    bind(sockfd, (struct sockaddr*) &addr1, SUN_LEN(&addr1));
    
    // 
    socklen_t len = sizeof(addr2);
    getsockname(sockfd, (struct sockaddr*) &addr2, &len);
    printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
    return 0;
}
