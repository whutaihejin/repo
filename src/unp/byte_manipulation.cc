#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 5

int main() {
    char buf[MAX_BUFFER_SIZE] = {0};
    memset(buf, 'l', MAX_BUFFER_SIZE - 1);
    printf("buf=%s\n", buf);
    char b2[MAX_BUFFER_SIZE];
    b2[MAX_BUFFER_SIZE - 1] = '\0';
    printf("before copy b2=%s\n", b2);
    memcpy(b2, buf, MAX_BUFFER_SIZE);
    printf("after copy b2=%s\n", b2);
    printf("comp=%d\n", memcmp(buf, b2, MAX_BUFFER_SIZE));
    buf[0] = 'a';
    printf("comp=%d\n", memcmp(buf, b2, MAX_BUFFER_SIZE));
    buf[0] = 'y';
    printf("comp=%d\n", memcmp(buf, b2, MAX_BUFFER_SIZE));
    return 0;
}
