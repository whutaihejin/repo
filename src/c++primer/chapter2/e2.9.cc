#include <iostream>

int main() {
    // expected '(' for function-style cast or type construction
    // std::cin >> int input_value;
    // error: use of undeclared identifier 'wage'
    // double salary = wage = 9999.99;
    // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
    // int i = {3.14};
    int i = 3.14;
    return 0;
}
