#include <iostream>

void BaseConversion(int n, int base, std::string& rst) {
    if (n < base) {
        rst.push_back(n + '0');
        return;
    }
    BaseConversion(n / base, base, rst);
    rst.push_back(n % base + '0');
}

int main() {
    std::string rst;
    BaseConversion(12345, 8, rst);
    std::cout << rst << std::endl;
    return 0;
}
