#include <iostream>
#include <arpa/inet.h>

int main() {
    // inet_pton
    struct in_addr in;
    const char* str = "100.90.71.41";
    if (inet_pton(AF_INET, str, &in) == 1) {
        std::cout << "str: " << str << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_pton with " << str << std::endl;
    }
   
    int r = 0;
    if ((r = inet_pton(AF_INET6, str, &in)) == 1) {
        std::cout << "str: " << str << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_pton with " << str << " ret: " << r << std::endl;
    }

    //
    const char* str1 = "100.90.71.410";
    int ret = 0;
    if ((ret = inet_pton(AF_INET, str1, &in)) == 1) {
        std::cout << "str1: " << str1 << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_pton with " << str1  << " ret: " << ret << std::endl;
    }
    
    if ((ret = inet_pton(AF_INET6, str1, &in)) == 1) {
        std::cout << "str1: " << str1 << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_pton with " << str1  << " ret: " << ret << std::endl;
    }
   
    const char* xx = "xx";
    if ((ret = inet_pton(AF_INET, xx, &in)) == 1) {
        std::cout << "str1: " << xx << in.s_addr << std::endl;
    } else {
        std::cout << "occur error using inet_pton with " << xx << " ret: " << ret << std::endl;
    }
  
    // inet_ntop
    char present[INET_ADDRSTRLEN] = {0};
    const char* ptr = inet_ntop(AF_INET, &in.s_addr, present, sizeof(present));
    std::cout << "ptr: " << ptr << " present: " << present << std::endl;
    
    return 0;
}
