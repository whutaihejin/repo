#include <iostream>
#include "common.h"

int main() {
    const int i = 42;
    auto j = i; // auto deduced as 'int'
    const auto &k = i;
    auto &kk = i;
    // cannot assign to variable 'k' with const-qualified type 'const int &'
    // k = 1;
    // kk = 2;
    auto *p = &i; // auto deduced as 'const int*'
    const auto j2 = i, &k2 = i; // auto duduced as 'const int'
    return 0;
}
