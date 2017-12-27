#include <iostream>

int f() {
    return 2;
}

int main() {
    int i = 42;
    int& r = i;
    //int&& rr = i;
    // int& r2 = i * 42;
    const int& r3 = i * 42;
    int&& rr2 = i * 42;
    
    //
    // int& x = f();
    int&& xx = f();

    //
    int&& y = 42;
    // int&& yy = y;
    int&& yy = std::move(y);
    return 0;
}
