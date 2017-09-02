#include <stdio.h>
#include <netinet/in.h>

int main() {
    uint16_t v16 = 16;
    printf("v16=%u ==> net v16=%d\n", v16, htons(v16));
    printf("net v16=%u ==> v16=%d\n", htons(v16), ntohs(htons(v16)));

    uint32_t v32 = 32;
    printf("v32=%u ==> net v32=%d\n", v32, htonl(v32));
    printf("net v32=%u ==> v32=%d\n", htonl(v32), ntohl(htonl(v32)));
    return 0;
}
