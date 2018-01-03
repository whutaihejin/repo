#include <iostream>

class Base {
public:
    Base(int val = 0): val_(val) {
        std::cout << "Base()=" << val_ << std::endl;
        Fun();
    }

    Base(const Base& b): val_(b.val_) {
        std::cout << "Base(const Base&)=" << val_ << std::endl;
    }

    Base(Base&& b): val_(b.val_) {
        std::cout << "Base(const Base&&)=" << val_ << std::endl;
    }

    Base& operator=(const Base& b) {
        val_ = b.val_;
        std::cout << "Base& operator=(const Base&)=" << val_ << std::endl;
        return *this;
    }

    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }

    virtual void Fun() {
        std::cout << "Base::Fun()" << std::endl;
    }

private:
    int val_;
};

class Derived : public Base {
public:
    Derived(int val = 1, int count = 2): Base(val), count_(count) {
        std::cout << "Derived()=" << count_ << std::endl;
        Fun();
    }

    Derived(const Derived& d): Base(d), count_(d.count_) {
        std::cout << "Derived(const Derived&)=" << count_ << std::endl;
    }
    
    Derived(Derived&& d): Base(std::move(d)), count_(d.count_) {
        std::cout << "Derived(const Derived&&)=" << count_ << std::endl;
    }

    virtual void Fun() {
        std::cout << "Derived::Fun()" << std::endl;
    }

    virtual ~Derived() {
        std::cout << "~Derived" << std::endl;
    }

private:
    int count_;

};

int main() {
    Derived d;
    Derived x(d);
    Derived xx(std::move(d));
    return 0;
}
