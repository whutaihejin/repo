#include <iostream>

template <typename T>
T Fobject(T x, T) {
    return x;
}

template <typename T>
T Frefrence(const T& x, const T&) {
    return x;
}

template <typename T>
int Compare(const T& x, const T& y) {
    if (x < y) {
        return -1;
    } else if (y < x) {
        return 1;
    }
    return 0;
}

template <typename T> void Fun1(T& x) {
    std::cout << x << std::endl; 
    // T a = "std";
}

template <typename T> void Fun2(const T& x) {
    std::cout << x << std::endl;
    // error: cannot initialize a variable of type 'int' with an lvalue of type 'const char [4]'
    // T a = "std";
}

template <typename T> void Fun3(T&& x) {
    std::cout << x << std::endl;
    T val = x;
    val = 111;
    if (val == x) {
        std::cout << "val=" << val << " == " << "x=" << x << std::endl;
    } else {
        std::cout << "val=" << val << " != " << "x=" << x << std::endl;
    }
    // error: cannot initialize a variable of type 'int' with an lvalue of type 'const char [4]'
    // error: non-const lvalue reference to type 'int' cannot bind to a value of unrelated type 'const char [4]'
    // int val = 2;
    // T a = val;
}

int main() {
    int it = 1;
    // note: in instantiation of function template specialization 'Fun3<int &>' requested here
    Fun3(it);
    Fun3(33);

    std::string s1("a value");
    const std::string s2("another value");
    Fobject(s1, s2);
    Frefrence(s1, s2);

    //
    int a[10] = {0};
    int b[20] = {0};
    Fobject(a, b);
    // candidate template ignored: deduced conflicting types for parameter 'T' ('int [10]' vs. 'int [20]')
    // Frefrence(a, b);
    
    //
    long x = 11L;
    // note: candidate template ignored: deduced conflicting types for parameter 'T' ('long' vs. 'int')
    // Compare(x, 22);
    Compare<long>(x, 22);

    //
    int i = 1;
    const int ci = 2;
    Fun1(i); // int
    Fun1(ci); // const int
    // candidate function [with T = int] not viable: expects an l-value for 1st argument
    // Fun1(3);
    
    Fun2(i); // int
    Fun2(ci); // int
    Fun2(3); // int
    int&& xxxx = 2;
    int& yyyy = xxxx;
    // non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
    // int& yyyy = 3;

    //
    Fun3(3); // int
    return 0;
}
