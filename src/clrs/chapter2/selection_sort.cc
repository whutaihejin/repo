#include <iostream>
#include <vector>

void SelectionSort(std::vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
        int min = i;
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[j] < nums[min]) {
                min = j;
            }
        }
        if (min != i) {
            int tmp = nums[i];
            nums[i] = nums[min];
            nums[min] = tmp;
        }
    }
}

void Show(std::vector<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> nums{31, 41, 59, 26, 41, 58};
    Show(nums);
    SelectionSort(nums);
    Show(nums);
    return 0;
}
