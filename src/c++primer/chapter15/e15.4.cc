#include <iostream>

class Base {};

// class Derived : public Derived {};

class Derived1 : private Base {};

// class Derived2 : public Base;

int main() {
    return 0;
}
