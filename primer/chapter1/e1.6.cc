#include <iostream>

int main() {
    int v1 = 3, v2 = 5;
    std::cout << "The sum of " << v1;
    // error: expected expression
    // << " and " << v2;
    // error: expected expression
    // << " is " << v1 + v2 << std::endl;
    std::cout << " and " << v2;
    std::cout << " is " << v1 + v2 << std::endl;
    return 0;
}
