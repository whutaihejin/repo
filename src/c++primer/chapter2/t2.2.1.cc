#include <iostream>

#define print(x) std::cout << #x"=" << x << std::endl;

int main() {
    int sum = 0, value, units_sold = 0;
    print(sum);
    print(value);
    print(units_sold);
    std::string book("0-201-78345");
    print(book);

    //
    double price = 109.99, discount = price * 0.16;
    print(price);
    print(discount);

    //
    int x1 = 0;
    int x2 = {0};
    int x3{0};
    int x4(0);
    print(x1);
    print(x2);
    print(x3);
    print(x4);

    //
    long double ld = 3.1415926536;
    // error: type 'long double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
    // int a{ld}, b = {ld};
    int c(ld), d = ld;
    return 0;
}
