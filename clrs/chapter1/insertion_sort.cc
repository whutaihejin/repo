#include <iostream>
#include <vector>
#include <algorithm>

void InsertionSort(std::vector<int>& nums) {
    int limit = nums.size();
    for (int i = 1; i < limit; ++i) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

void InsertionSortDesc(std::vector<int>& nums) {
    int limit = nums.size();
    for (int i = 1; i < limit; ++i) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] < key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

int main() {
    std::vector<int> nums{5, 2, 4, 6, 1, 3};
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    InsertionSort(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    InsertionSortDesc(nums);
    std::for_each(nums.begin(), nums.end(), [](const int& x) { std::cout << x << ", "; }); std::cout << std::endl;
    return 0;
}
