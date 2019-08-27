#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf buf;

int parseLine();
int parseToten();

int main() {
    int place = 0;
    if ((place = setjmp(buf)) != 0) {
        printf("error occur from: %d\n", place);
        exit(1);
    } else {
        printf("first call setjmp\n");
    }
    parseLine();
    return 0;
}

int parseLine() {
    printf("I am parseLine\n");
    parseToten();
    return 0;
}

int parseToten() {
    printf("I am parse token\n");
    longjmp(buf, 1);
    return 0;
}
