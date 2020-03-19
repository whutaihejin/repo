#include <iostream>
#include <functional>

void f(int& v) {
    ++v;
}

int main() {
    int v  = 1;
    auto bind_f = std::bind(f, v);
    bind_f();
    std::cout << "v=" << v << std::endl;

    auto bind_r = std::bind(f, std::ref(v));
    bind_r();
    std::cout << "v=" << v << std::endl;
    return 0;
}
