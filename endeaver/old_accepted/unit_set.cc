#include <iostream>
#include <vector>

int Set(double nums[], int size) {
    std::vector<int> f(size + 1, 0);
    for (int i = 1; i <= size; ++i) {
        int k = i;
        for (; k >= 1 && nums[k - 1] >= nums[i - 1] - 1; k--) {
        }
        std::cout << i << " -> " << k << std::endl;
        f[i] = f[k] + 1;
    }
    for (int i = 0; i <= size; ++i) {
        std::cout << i  << " -> " << f[i] << std::endl;
    }
    return f[size];
}

int main() {
    {
        double nums[] = {0.1, 0.2, 0.3, 0.4, 5};
        int val = Set(nums, 5);
        std::cout << "answer: " << val << std::endl;
    }
    {
        double nums[] = {1, 2, 3, 4, 5};
        int val = Set(nums, sizeof(nums) / sizeof(nums[0]));
        std::cout << "answer: " << val << std::endl;
    }
    return 0;
}
