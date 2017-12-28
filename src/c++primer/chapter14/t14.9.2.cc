#include <iostream>

struct B;
struct A {
    A(int val): val_(val) {}
    A(const B&) {}
private:
    int val_;
};

struct B {
public:
    explicit operator A() const {
        return A(vv_);
    }

private:
    int vv_;
};

void f(const A&) {
}
int main() {
    B b;
    // error: reference initialization of type 'const A &' with initializer of type 'B' is ambiguous
    f(b);
    f(static_cast<A>(b));
    return 0;
}
