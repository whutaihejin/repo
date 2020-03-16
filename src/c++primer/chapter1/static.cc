#include <iostream>

int gen() {
    std::cout << "gen -> " << 1 << std::endl;
    return 1;
}

void f() {
    static int x = gen();
    // int x = gen();
    std::cout << "f -> " << x << std::endl;
}

int main() {
    f();
    f();
    return 0;
}
