#include <iostream>

int main() {
    int tests = 0;
    std::cin >> tests;
    for (int i = 0; i < tests; ++i) {
        long long val = 0;
        std::cin >> val;
        val = 2 * val * val - val + 1;
        std::cout << val << std::endl;
    }
    return 0;
}
