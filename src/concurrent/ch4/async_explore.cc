#include <iostream>
#include <thread>
#include <future>

struct Fun {
    void Foo(int x, const std::string& name) {
        std::cout << "x=" << x << "|name=" << name << std::endl;
    }

    std::string Bar(const std::string& bar) {
        std::cout << "bar=" << bar << std::endl;
        return "done";
    }
};

int main() {
    Fun fun;
    auto f1 = std::async(&Fun::Foo, &fun, 22, "taihejin");
    auto f2 = std::async(&Fun::Bar, fun, "goodbye");
    f1.get();
    const std::string& name = f2.get();
    std::cout << "name=" << name << std::endl;
    return 0;
}
