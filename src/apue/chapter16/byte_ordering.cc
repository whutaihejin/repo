#include <stdio.h>
#include <stdint.h>

int main() {
    int val = 0x04030201;
    uint8_t* p = reinterpret_cast<uint8_t*>(&val);
    if (*p == 0x01) {
        printf("little endian\n");
    } else {
        printf("big endian\n");
    }
    uint8_t* limit = p + sizeof(int);
    for (; p < limit; ++p) {
        printf("%u ", *p);
    }
    printf("\n");
    return 0;
}
