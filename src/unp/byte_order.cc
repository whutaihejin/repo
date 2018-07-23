#include <iostream>
#include <netinet/in.h>

int main() {
    union un {
        short val;
        char ch[sizeof(short)];
    };
    un x;
    x.val = 0x0102;
    if (sizeof(short) == 2U) {
        if (x.ch[0] == 0x02 && x.ch[1] == 0x01) {
            std::cout << "little endian" << std::endl;
        } else if (x.ch[0] == 0x01 && x.ch[1] == 0x02) {
            std::cout << "big-endian" << std::endl;
        } else {
            std::cout << "unknown" << std::endl;
        }
    } else {
        std::cout << "sizeof(short)=" << sizeof(short) << std::endl;
    }

    uint16_t port = 8019;
    std::cout << "host port:" << port << " net port:" << htons(port) << std::endl;
    std::cout << "net port:" << htons(port) << " host port:" << ntohs(htons(port)) << std::endl;
    uint32_t val = 8022;
    std::cout << "host val:" << val << " net val:" << htonl(val) << std::endl;
    std::cout << "net val:" << htonl(val) << " net val:" << ntohl(htonl(val)) << std::endl;

    return 0;
}
