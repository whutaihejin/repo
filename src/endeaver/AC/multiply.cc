#include <iostream>

int Multiply(uint32_t a, uint32_t b) {
    int p = 0, i = 0;
    while (b) {
        if (b & 0x01) {
            p += (a << i);
        }
        b >>= 1;
        i++;
    }
    return p;
}

int main() {
    int a = 0, b = 0;
    while (std::cin >> a >> b) {
        std::cout << (a * b) << " = " << Multiply(a, b) << std::endl;
        std::cout << "Enter to integer numbers:";
    }
    return 0;
}
