#include <iostream>
#include <string>
#include <stdio.h>

int main() {
    std::string s1 = "I am a superman!";
    std::string s2 = s1;
    printf("Sharing the memory:\n");
    printf("s1 address: %x\n", s1.c_str());
    printf("s2 address: %x\n", s2.c_str());
    s1[0] = 'X';
    s2[0] = 'Y';
    printf("After Copy-On-Write:\n");
    printf("s1 address: %x\n", s1.c_str());
    printf("s2 address: %x\n", s2.c_str());
    return 0;
}
