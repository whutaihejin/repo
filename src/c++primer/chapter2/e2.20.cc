#include <iostream>
#include "common.h"

int main() {
    int i = 42;
    int *p = &i;
    *p = *p * *p;
    std::cout << i << " " << p << std::endl;
    return 0;
}
