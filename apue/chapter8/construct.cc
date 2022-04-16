#include <stdio.h>

class A {
public:
    A() {
        printf("constructor of A%p\n", this);
    }

    ~A() {
        printf("destory of A %p\n", this);
    }
};

int main() {
    A* pa = new A[3];
    delete[] pa;
    
    A* pb = new A[2];
    delete pb;
    return 0;
}
