#include <iostream>

int modular(int b, int n, int m) {
    int r = 1, i = 0;
    int power = b % m;
    while (n) {
        if (n & 0x01) {
            r = r * power % m;
        }
        power = power * power % m;
        std::cout << i++ << " a" << (n & 0x01) << " r" << r << " p" << power << std::endl;
        n >>= 1;
    }
    return r;
}

int main() {
    int b = 3, n = 644, m = 645;
    int r = modular(b, n, m);
    std::cout << "r = " << r << std::endl;
    return 0;
}
