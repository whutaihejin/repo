#include <iostream>

int main() {
    const int ci = 0, &cj = ci;
    decltype(ci) x = 0; // const int
    decltype(cj) y = x; // const int&
    // declaration of reference variable 'z' requires an initializer
    // decltype(cj) z; 
    
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;
    // declaration of reference variable 'c' requires an initializer
    // decltype(*p) c;
   
    // declaration of reference variable 'd' requires an initializer
    // decltype((i)) d;
    decltype(i) e;
    return 0;
}
