#include <stdio.h>

int main() {
    printf("%'10d\n", 123123124);
    printf("%-10d\n", 12232);
    printf("%+10d\n", 23232);
    printf("%+10d\n", -23232);
    printf("% 10d\n", 23232);
    printf("%#10x\n", 23232);
    printf("%010d\n", 23232);
    printf("%d,%i\n", 111, 222);
    printf("%#o\n", 10);
    printf("%u\n", 10);
    printf("%x, %X\n", 12, 12);
    printf("%f, %F\n", 12.12, 22.22);
    printf("%e, %E\n", 12000.12, 2002.22);
    printf("%g, %G\n", 121213213.02412312, 12121.2);
    printf("%a, %A\n", 121212312.321, 212.2);
    printf("%c,%c\n", 'c', 'b');
    printf("[%s]\n", "taihejin");
    size_t val = 22;
    printf("%p\n", &val);
    int v = 0;
    printf("hello%n, world:", &v);
    printf("%d\n", v);
    printf("%%\n");
    printf("%zu\n", val);
    printf("%zd\n", val);
    printf("%c\n", 'c');
    short sv = 11;
    printf("%hd\n", sv);
    printf("%ld\n", 22L);
    printf("%lld\n", 22LL);
    int r = printf("%llu\n", 22LLU);
    printf("%d\n", r);
    return 0;
}
