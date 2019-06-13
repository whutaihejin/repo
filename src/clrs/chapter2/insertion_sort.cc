#include <iostream>
#include <vector>

void InsertionSort(std::vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        int key = nums[i];
        int j = i - 1;
        for (; j >= 0 && key < nums[j]; --j) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = key;
    }
}

void Show(std::vector<int>& nums) {
    for_each(nums.begin(), nums.end(), [](const int& v) { std::cout << v << " "; });
    std::cout << std::endl;
}

int main() {
    std::vector<int> nums{31, 41, 59, 26, 41, 58};
    Show(nums);
    InsertionSort(nums);
    Show(nums);
    return 0;
}
