#include <stdio.h>

int main() {
    int a = -3;
    unsigned int b = 2;
    long c = a + b;
    printf("sizeof(long)=%ld\n", sizeof(long));
    printf("%ld\n", c);
    return 0;
}
