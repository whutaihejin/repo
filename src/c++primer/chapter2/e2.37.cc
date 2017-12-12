#include <iostream>

int main() {
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype(a = b) d = a;
    d = 2;
    std::cout << "a=" << a << std::endl;
    std::cout << "b=" << b << std::endl;
    std::cout << "c=" << c << std::endl;
    std::cout << "d=" << d << std::endl;
    return 0;
}
