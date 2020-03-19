#include <iostream>

int main() {
    int x[10] = {0};
    for (size_t i = 0; i < 10; ++i) {
        x[i] = i;
    }
    int xx[10] = {0};
    for (size_t i = 0; i < 10; ++i) {
        xx[i] = x[i];
    }
    for (auto i : xx) {
        std::cout << i << std::endl;
    }
}
