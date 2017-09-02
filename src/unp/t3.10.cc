#include <stdio.h>

int main() {
    union length {
        short s;
        char c[sizeof(short)];
    };
    union length l;
    l.s = 0x0102;
    if (sizeof(short) == 2L) {
        if (l.c[0] == 1 && l.c[1] == 2) {
            printf("big-endian\n");
        } else if (l.c[0] == 2 && l.c[1] == 1) {
            printf("little-endian\n");
        } else {
            printf("unknown\n");
        }
    } else {
        printf("sizeof(short)=%ld\n", sizeof(short));
    }
    return 0;
}
