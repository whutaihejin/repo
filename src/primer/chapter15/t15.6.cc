#include <iostream>

class Base {
public:
    Base(): member_(1) {}
    void f() {
        std::cout << "base f" << std::endl;
    }
private:
    int member_;
};

class Derived : public Base {
public:
    Derived(): member_(2) {}

    // declare 'f' of base class
    using Base::f;

    void f(int x) {
        std::cout << x << std::endl;
    }

    void f(char x) {
        std::cout << x << std::endl;
    }

    void Display() {
        std::cout << member_ << std::endl;
    }
private:
    int member_;
};

int main() {
    Base b;
    Derived d;
    b.f();
    d.f(0);
    // error: no matching member function for call to 'f'
    d.f();
    d.f('a');
    d.Base::f();
    d.Display();
    return 0;
}
