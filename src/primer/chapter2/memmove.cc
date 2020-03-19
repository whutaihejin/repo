#include <string.h>
#include <stdio.h>

int main() {
    char str[] = "hello wolrd";
    size_t size = sizeof(str);
    char copy[100] = {0};
    memmove(copy, str, size);
    printf("str=%s\n", str);
    printf("size=%s\n", copy);
    return 0;
}
