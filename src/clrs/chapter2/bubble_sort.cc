#include <iostream>
#include <vector>
#include <algorithm>

void BubbleSort(std::vector<int>& nums) {
    for (int i = nums.size(); i > 1; --i) {
        for (int j = 1; j < i; j++) {
            if (nums[j - 1] > nums[j]) {
                int tmp = nums[j - 1];
                nums[j - 1] = nums[j];
                nums[j] = tmp;
            }
        }
    }
}

void Show(std::vector<int>& nums) {
    std::for_each(nums.begin(), nums.end(), [](const int& v) { std::cout << v << " "; });
    std::cout << std::endl;
}

int main() {
    std::vector<int> nums{31, 41, 58, 41, 59};
    Show(nums);
    BubbleSort(nums);
    Show(nums);
    return 0;
}
