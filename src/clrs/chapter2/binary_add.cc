#include <iostream>
#include <vector>
#include <algorithm>

int BinaryAdd(std::vector<int>& a, std::vector<int>& b, std::vector<int>& s) {
    s.resize(a.size() + 1);
    int carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        s[i] = (a[i] + b[i] + carry) & 0x01;
        carry = (a[i] + b[i] + carry) >> 1;
    }
    s[a.size()] = carry;
    return 0;
}

void Show(std::vector<int>& nums) {
    std::for_each(nums.begin(), nums.end(), [](const int& v) { std::cout << v; });
    std::cout << std::endl;
}

int main() {
    {
        std::vector<int> a{0, 0};
        std::vector<int> b{0, 0};
        std::vector<int> c;
        BinaryAdd(a, b, c);
        Show(a);
        Show(b);
        std::cout << "sum:";
        Show(c);
    }
    {
        std::vector<int> a{0, 1};
        std::vector<int> b{0, 0};
        std::vector<int> c;
        BinaryAdd(a, b, c);
        Show(a);
        Show(b);
        std::cout << "sum:";
        Show(c);
    }
    {
        std::vector<int> a{1, 0};
        std::vector<int> b{0, 0};
        std::vector<int> c;
        BinaryAdd(a, b, c);
        Show(a);
        Show(b);
        std::cout << "sum:";
        Show(c);
    }
    {
        std::vector<int> a{1, 1};
        std::vector<int> b{0, 0};
        std::vector<int> c;
        BinaryAdd(a, b, c);
        Show(a);
        Show(b);
        std::cout << "sum:";
        Show(c);
    }
    {
        std::vector<int> a{1, 1};
        std::vector<int> b{1, 1};
        std::vector<int> c;
        BinaryAdd(a, b, c);
        Show(a);
        Show(b);
        std::cout << "sum:";
        Show(c);
    }
    return 0;
}
