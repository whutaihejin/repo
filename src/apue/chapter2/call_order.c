#include <stdio.h>

void foo(int a, int b) {
    printf("%d, %d\n", a, b);
}

int getNum() {
    static int i = 0;
    return ++i;
}

int main() {
    foo(getNum(), getNum());
    return 0;
}
