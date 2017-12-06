#include <iostream>

int main() {
    std::cout << "Enter two numbers" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    if (v1 > v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    for (; v1 <= v2; ++v1) {
        std::cout << v1 << " ";
    }
    std::cout << std::endl;
    return 0;
}
