#include <iostream>

int main() {
    int sum = 0;
    for (int i = 50; i <= 100; ++i) {
        sum += i;
    }
    std::cout << sum << std::endl;

    // 10 to 0
    for (int i = 10; i >= 0; --i) {
       std::cout << i << " ";
    }
    std::cout << std::endl;

    // x to y
    std::cout << "Enter two numbers" << std::endl;
    int x = 0, y = 0;
    std::cin >> x >> y;
    for (; x <= y; ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
