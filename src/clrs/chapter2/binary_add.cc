#include <iostream>
#include <vector>
#include <algorithm>

int BinaryAdd(std::vector<int>& a, std::vector<int>& b, std::vector<int>& s) {
    s.resize(a.size() + 1);
    int carry = 0, i = a.size() - 1;
    for (; i >= 0; i--) {
        s[i + 1] = (a[i] + b[i] + carry) & 0x01;
        carry = (a[i] + b[i] + carry) >> 1;
    }
    s[0] = carry;
    return 0;
}

void Show(std::vector<int>& nums, std::vector<int>* next = NULL, std::vector<int>* sum = NULL) {
    std::for_each(nums.begin(), nums.end(), [](const int& v) { std::cout << v; });
    if (next) {
        std::cout << " + ";
        std::for_each(next->begin(), next->end(), [](const int& v) { std::cout << v; });
    }
    if (sum) {
        std::cout << " = ";
        std::for_each(sum->begin(), sum->end(), [](const int& v) { std::cout << v; });
    }
    std::cout << std::endl;
}

int main() {
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            std::vector<int> a{(i & 0x02) >> 1, i & 0x01};
            std::vector<int> b{(j & 0x02) >> 1, j & 0x01};
            std::vector<int> c;
            BinaryAdd(a, b, c);
            Show(a, &b, &c);
        }
    }
    return 0;
}
