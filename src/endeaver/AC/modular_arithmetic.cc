#include <iostream>
#include <stdio.h>

void Modular(int dividend, int divisor) {
    if (divisor == 0) {
        printf("invalid divisor: %d\n", divisor);
        return;
    }
    printf("%d div %d = %d\n", dividend, divisor, dividend / divisor);
    printf("%d mod %d = %d\n", dividend, divisor, dividend % divisor);
}

int main() {
    Modular(101, 11);
    Modular(-11, 3);
    Modular(11, -3);
    Modular(-11, -3);
    return 0;
}
