#include <iostream>
#include <vector>
#include <algorithm>

void SelectionSort(std::vector<int>& nums) {
    int limit = nums.size();
    for (int i = 0; i < limit; ++i) {
        int min = i; // only record min index
        for (int j = i + 1; j < limit; ++j) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        std::swap(nums[i], nums[min]);
    }
}

void SelectionSortDesc(std::vector<int>& nums) {
    int limit = nums.size();
    for (int i = 0; i < limit; ++i) {
        int max = i;
        for (int j = i + 1; j < limit; ++j) {
            if (nums[j] > nums[max]) {
                max = j;
            }
        }
        std::swap(nums[i], nums[max]);
    }
}

int main() {
    std::vector<int> nums{5, 2, 4, 6, 1, 3};
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    SelectionSort(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    SelectionSortDesc(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    return 0;
}
