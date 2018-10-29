#include <iostream>
#include <vector>

int f() {
    return 0;
}
int main() {
    // section 1
    {
        int i = 22;
        int& r = i;
        // int&& rr = i; // cannot bind ‘int’ lvalue to ‘int&&’
        // int& r2 = i * 42; // invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
        const int& r3 = i * 42;
        int&& rr2 = i * 42;
    }

    // section 2
    {
        std::vector<int> v(100);
        int&& r1 = f();
        int& r2 = v[0];
        int& r3 = r1;
        int&& f4 = v[0] * f();
    }
    return 0;
}
