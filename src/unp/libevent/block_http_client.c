#include <netinet/in.h> // for sockaddr_in
#include <sys/socket.h> // for socket functions
#include <netdb.h> // for gethostbyname

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    const char query[] = "GET / HTTP/1.0\r\nHost: www.baidu.com\r\n\r\n";
    const char hostname[] = "www.baidu.com";
    struct sockaddr_in addr;
    struct hostent* h = NULL;
    const char* cp;
    int fd;
    ssize_t n_written, remaining;
    char buf[1024];
    
    // Look up the IP address fro the hostname. Watch out; this isn't threadsafe on most platforms.
    h = gethostbyname(hostname);
    if (!h) {
        fprintf(stderr, "Couldn't lookup %s: %s", hostname, hstrerror(h_errno));
        return 1;
    }
    if (h->h_addrtype != AF_INET) {
        fprintf(stderr, "No ipv6 support, sorry.");
        return 1;
    }

    // Allocate a new socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    // Connect to the remote host
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr = *(struct in_addr*)h->h_addr;
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
        perror("connect");
        close(fd);
        return 1;
    }
    
    // write the query
    // xxx can send succeed partially?
    cp = query;
    remaining = strlen(query);
    while (remaining) {
        n_written = send(fd, cp, remaining, 0);
        if (n_written <= 0) {
            perror("send");
            return 1;
        }
        remaining -= n_written;
        cp += n_written;
    }
    
    // Get an answer back
    for (;;) {
        ssize_t result = recv(fd, buf, sizeof(buf), 0);
        if (result == 0) {
            break;
        } else if (result < 0) {
           perror("recv");
           close(fd);
           return 1;
        }
        fwrite(buf, 1, result, stdout);
    }
    close(fd);
    return 0;
}
