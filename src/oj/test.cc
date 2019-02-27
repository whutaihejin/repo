#include <iostream>
#include <stdio.h>

char* getMemory() {
    char p[] = "hello world";
    return p;
}

int main() {
    short s = 65535;
    std::cout << s << " " << s + 1 << std::endl;
    unsigned short us = 65535;
    std::cout << us << " " << us + 1 << std::endl;
    std::cout << us + 2 << " " << us + 3 << std::endl;


    char* str = nullptr;
    str = getMemory();
    printf("%s\n", str);
    // std::cout << str << std::endl;
    return 0;
}
