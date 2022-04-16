#include <iostream>
#include "common.h"

int main() {
    int i = 22, &r = i;
    auto a = r;
    const int ci = i, &cr = ci;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;
    const auto f = ci;
    auto &g = ci;

    //
    a = 42;
    b = 42;
    c = 42;
    // assigning to 'int *' from incompatible type 'int'
    // d = 42;
    // assigning to 'const int *' from incompatible type 'int'
    // e = 42;
    // cannot assign to variable 'g' with const-qualified type 'const int &'
    // g = 42;
    std::cout << "a=" << a <<
        " b=" << b <<
        " c=" << c <<
        " d=" << d <<
        " e=" << e <<
        " f=" << f <<
        " g=" << g << std::endl;
    return 0;
}
