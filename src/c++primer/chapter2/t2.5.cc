#include <iostream>
#include "common.h"

typedef int *pint;
int main() {
    int ival = 1;
    pint p1 =  &ival;
    // aka: int *const
    const pint p2 = &ival;
    // warning: duplicate 'const' declaration specifier [-Wduplicate-decl-specifier]
    // const pint const px = &ival;
    const pint *p3 = &p2; // int** const
    // const pint *const p3 = &p2;
    std::cout << **p3 << " " << *p2  << " " << *p1 << std::endl;
    int x = 2;
    const pint px = &x;
    p3 = &px;

    //
    int v1 = 2, v2 = 3;
    auto v3 = v1 + v2;
    std::cout << v3 << std::endl;
    auto i = 0, *p = &i;
    // error: 'auto' deduced as 'int' in declaration of 'sz' and deduced as 'double' in declaration of 'pi'
    // auto sz = 0, pi = 3.14;
    int iv = 0, &r = iv;
    auto a = r;
    const int ci = i, &cr = ci;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci; // 对常量对象取地址是一种底层const
    const auto f = ci;

    // reference
    auto &g = ci;
    // non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
    // auto &h = 42;
    const auto &j = 42;

    //
    auto k = ci, &l = i;
    auto &m = ci, *ppp = &ci;
    // 'auto' deduced as 'int' in declaration of 'n' and deduced as 'const int' in declaration of 'p6'
    // auto &n = i, *p6 = &ci;
    return 0;
}
