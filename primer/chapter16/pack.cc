#include <iostream>
#include <string>

template <typename T, typename... Args>
void foo(const T &t, const Args&... rest) {
    std::cout << "number of type parameters: " << sizeof...(Args) << std::endl;
    std::cout << "number of function parameters: " << sizeof...(rest) << std::endl;
}

template <typename... Args> void g(Args... args) {
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(args) << std::endl;
}

// function to end the recursive and print the last element
// this function must be declared before the variadic version of print is defined
template <typename T>
std::ostream& print(std::ostream& os, const T &t) {
    return os << "d|" << t << std::endl; // no separator after the last element in the pack
}

// this version of print will be called for all but the last element in the pack
template <typename T, typename... Args>
std::ostream& print(std::ostream &os, const T& t, const Args... rest) {
    os << "c|";
    os << t << ", "; // print the first argument
    return print(os, rest...); // recursive call; print the other arguments
}

int main() {
    int i = 0;
    double d = 3.14;
    std::string s = "how now brown cow";

    // void foo(const int&, const string&, const int&, const double&);
    foo(i, s, 42, d); // three parameters in the pack
    
    // void foo(const sting&, const int&, const char[3]&);
    foo(s, 42, "hi"); // two parameters in the pack
    
    // void foo(const double&, const string&);
    foo(d, s); // one parameter in the pack
    
    // void foo(const char[3]&);
    foo("hi"); // empty pack

    //
    std::cout << "-----" << std::endl;
    g("x");
    g(1, "x");
    g(1, 3.13, "x");

    // print
    print(std::cout, i, s, 42); // two parameters in the pack
    return 0;
}
