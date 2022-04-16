#include <iostream> 
#define str(x) #x"="
#define print(x) std::cout << str(x) << x << std::endl;

int main() {
    bool b = 42;
    print(b);
    int i = b;
    print(i);
    i = 3.14;
    print(i);
    double pi = i;
    print(pi);
    unsigned char c = -1;
    print(c);
    signed char c2 = 304;
    print(c2);
    return 0;
}
