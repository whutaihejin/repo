#include <iostream>

int main() {
    int x[10] = {0};
    for (size_t i = 0; i < 10; ++i) {
        x[i] = i;
    }
    for (auto i : x) {
        std::cout << i << std::endl;
    }
}
