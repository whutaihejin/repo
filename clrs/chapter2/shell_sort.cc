#include <iostream>
#include <vector>

void Show(std::vector<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void ShellSort(std::vector<int>& nums) {
    std::vector<int> deltas{10, 5, 3, 2, 1};
    for (size_t k = 0; k < deltas.size(); ++k) {
        int d = deltas[k];
        for (size_t i = d; i < nums.size(); ++i) {
            int key = nums[i];
            int j = i - d;
            for (; j >= 0 && key < nums[j]; j -= d) {
                nums[j + d] = nums[j];
            }
            nums[j + d] = key;
        }
        std::cout << "internal result by " << d << " steps" << std::endl;
        Show(nums);
    }
}

int main() {
    std::vector<int> nums{100, 41, 21, 59, 58};
    Show(nums);
    ShellSort(nums);
    Show(nums);
    return 0;
}
