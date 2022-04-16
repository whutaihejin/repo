#include <stdint.h>
#include <stdio.h>

int VarintLength(uint64_t v) {
    int c = 1;
    while (v >= 128) {
        v >>= 7;
        c++;
    }
    return c;
}

void EncodeVarint32(char* buf, uint32_t v) {
    while (v >= 128) {
        uint8_t g = (uint8_t)(v & 0x7f);
        buf[0] = (g | 0x80);
        buf += 1;
        v >>= 7;
    }
}

int main() {
    char buf[128];
    EncodeVarint32(buf, 150);
    return 0;
}
