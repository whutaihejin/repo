#include <iostream>
#include "common.h"

int main() {
    int i = 0, j = 1;
    int* p = &i;
    p = &j;
    *p = 3;
    std::cout << i << " " << j << " " << p << std::endl;
    return 0;
}
