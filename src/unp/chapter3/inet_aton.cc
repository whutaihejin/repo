#include <iostream>
#include <arpa/inet.h>

int main() {
    struct in_addr in;
    memset(&in, 0, sizeof(struct in_addr));
    std::cout << "s_addr: " << in.s_addr << std::endl;

    const char* ipstr0 = "100.90.71.41";
    if (inet_aton(ipstr0, &in) == 1) {
        std::cout << ipstr0 <<  " s_addr: " << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_aton " << ipstr0 << std::endl;
    }

    //
    std::cout << "inet_ntoa: " << inet_ntoa(in) << std::endl;
  
    const char* ipstr = "100.257.10.301";
    if (inet_aton(ipstr, &in) == 1) {
        std::cout << "s_addr: " << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_aton with " << ipstr << std::endl;
    }

    // inet_addr
    std::cout << ipstr0 << " " << inet_addr(ipstr0) << std::endl;
    std::cout << ipstr << " " << inet_addr(ipstr) <<  " INADDR_NONE: " << INADDR_NONE << std::endl;
    return 0;
}
