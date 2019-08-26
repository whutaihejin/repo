#include <stdio.h>

bool littleEndian() {
    int x = 0x01;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&x);
    return *ptr == 0x01;
}

int main() {
    bool is_little_endian = littleEndian();
    printf("detect system is %s endian\n", is_little_endian ? "little" : "big");
    return 0;
}
