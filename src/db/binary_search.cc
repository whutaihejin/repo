#include <iostream>
#include <vector>

int binarySearchLeft(std::vector<int>& nums, int key) {
    if (nums.empty()) return -1;
    int l = 0, h = nums.size() - 1;
    while (l + 1 < h) {
        int m = l + (h - l) / 2;
        if (key <= nums[m]) {
            h = m;
        } else {
            l = m + 1;
        }
    }
    return nums[l] == key ? l : (nums[h] == key ? h : -1);
}

int binarySearchRight(std::vector<int>& nums, int key) {
    if (nums.empty()) {
        return -1;
    }
    int l = 0, h = nums.size() - 1;
    while (l + 1 < h) {
        int m = l + (h - l) / 2;
        if (key >= nums[m]) {
            l = m;
        } else {
            h = m - 1;
        }
    }
    return nums[h] == key ? h : (nums[l] == key ? l : -1);
}

int main() {
    std::vector<int> nums{2, 2, 2, 2};
    int left = binarySearchLeft(nums, 2);
    int right = binarySearchRight(nums, 2);
    std::cout << "left=[" << left << "], right=[" << right << "]" << std::endl;
    return 0;
}
