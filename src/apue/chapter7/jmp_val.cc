#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf buf;

int parseLine(int v1, int v2, int v3, int v4, int v5);
int parseToten();

static int globval;

int main() {
    int autoval;
    register int regival;
    volatile int volaval;
    static int staval;
    globval = 1;
    autoval = 2;
    regival = 3;
    volaval = 4;
    staval = 5;


    int place = 0;
    if ((place = setjmp(buf)) != 0) {
        printf("error occur from: %d\n", place);
        printf("globval=%d, autoval=%d, regival=%d, volaval=%d, staval=%d\n", 
                globval, autoval, regival, volaval, staval);
        exit(1);
    } else {
        printf("first call setjmp\n");
    }

    globval = 101;
    autoval = 102;
    regival = 103;
    volaval = 104;
    staval = 105;
    parseLine(globval, autoval, regival, volaval, staval);
    return 0;
}

int parseLine(int v1, int v2, int v3, int v4, int v5) {
    printf("I am parse line\n");
    printf("globval=%d, autoval=%d, regival=%d, volaval=%d, staval=%d\n", 
            v1, v2, v3, v4, v5);
    parseToten();
    return 0;
}

int parseToten() {
    printf("I am parse token\n");
    longjmp(buf, 1);
    return 0;
}
