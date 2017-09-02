#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    struct in_addr addr;
   
    // normal argument
    const char* strptr = "10.12.80.89";
    if (inet_aton(strptr, &addr) != 1) {
        printf("%s inet_aton error\n", strptr);
    }
    // invalid argument
    const char* invalid_str = "999.12.80.89";
    if (inet_aton(invalid_str, &addr) != 1) {
        printf("%s inet_aton error\n", invalid_str);
    }
    // null addr
    if (inet_aton(strptr, NULL) != 1) {
        printf("%s inet_aton error\n", strptr);
    }

    // normal
    in_addr_t addr_val;
    if ((addr_val = inet_addr(strptr)) == INADDR_NONE) {
        printf("%s inet_addr error\n", strptr);
    }
    // boundary
    const char* addr_str = "255.255.255.255";
    if ((addr_val = inet_addr(addr_str)) == INADDR_NONE) {
        printf("%s inet_addr error\n", addr_str);
    }
    
    // invalid argument
    if ((addr_val = inet_addr(invalid_str)) == INADDR_NONE) {
        printf("%s inet_addr error\n", invalid_str);
    }

    // for inet_ntoa
    printf("inet_ntoa=%s\n", inet_ntoa(addr));

    memset(&addr, 0, sizeof(addr));
    printf("inet_ntoa=%s\n", inet_ntoa(addr));

    // for inet_pton
    if (inet_pton(AF_INET, strptr, &addr) != 1) {
        printf("%s inet_pton error\n", strptr);
    }
    if (inet_pton(AF_INET, invalid_str, &addr) != 1) {
        printf("%s inet_pton error\n", invalid_str);
    }

    // for inet_ntop
    char buf[INET_ADDRSTRLEN] = {0};
    if (inet_ntop(AF_INET, &addr, buf, sizeof(buf)) != NULL) {
        printf("inet_ntop %s\n", buf);
    }

    return 0;
}

