#include <iostream>

std::string BaseConversion(int n, int base) {
    if (n < base) {
        return std::string(1, n + '0');
    }
    std::string s = BaseConversion(n / base, base);
    s.push_back(n % base + '0');
    return s;
}

int main() {
    std::string s = BaseConversion(12345, 8);
    std::cout << s << std::endl;
    return 0;
}
