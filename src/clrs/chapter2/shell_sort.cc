#include <iostream>
#include <vector>

void DoShellSort(std::vector<int>& nums, int d) {
    for (int k = 0; k < d; ++k) {
        for (size_t i = k + d; i < nums.size(); i += d) {
            int key = nums[i];
            int j = i - d;
            for (; j >= 0 && key < nums[j]; j -= d) {
                nums[j + d] = nums[j];
            }
            nums[j + d] = key;
        }
    }
}

void Show(std::vector<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void ShellSort(std::vector<int>& nums) {
    std::vector<int> deltas{10, 5, 3, 2, 1};
    for (size_t i = 0; i < deltas.size(); ++i) {
        DoShellSort(nums, deltas[i]);
        std::cout << "shell sort by " << deltas[i] << std::endl;
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
