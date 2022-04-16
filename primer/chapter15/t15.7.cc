#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base()" << std::endl;
    }

    Base(const Base& b) = delete;

    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived()" << std::endl;
    }

    virtual ~Derived() {
        std::cout << "~Derived()" << std::endl;
    }
};

int main() {
    Base* b = new Base;
    // Base* bb = new Base();
    delete b;
    // delete bb;
    Base* d = new Derived();

    //
    Derived xd;
    Derived xxd;
    // error: no matching constructor for initialization of 'Derived'
    // Derived xxxd(std::move(d));
    
    // error: call to implicitly-deleted copy constructor of 'Derived'
    // Derived xxxd(xd);
    delete d;
    return 0;
}
