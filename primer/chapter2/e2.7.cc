#include <iostream>

int main() {
    const char* str = "A\12A";
    const char* s2 = "A\012A";
    std::cout << str << std::endl;
    std::cout << "H\012H" << std::endl;
    return 0;
}
