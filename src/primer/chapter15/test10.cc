#include <stdio.h>
#include <iostream>

class A {
public:
    void print() {
        std::cout << "A print" << std::endl;
    }
};

class B: private A {
public:
    void print() {
        std::cout << "B print" << std::endl;
    }
};

class C: public B {
public:
    void print() {
//        A::print();
    }
};

int main() {
    int a = -3;
    unsigned int b = 2;
    long c = a + b;
    printf("sizeof(long)=%ld\n", sizeof(long));
    printf("%ld\n", c);

    //
    // void& p = 1;
    
    C d;
    d.print();
    return 0;
}
