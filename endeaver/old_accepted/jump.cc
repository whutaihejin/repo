#include <iostream>
#include <vector>

int j(std::vector<int>& nums) {
    int step = 0;
    int far = 0, limit = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i > limit) {
            limit = far;
            step++;
        }
        far = std::max(far, nums[i] + i);
    }
    return step;
}

int main() {
    std::vector<int> nums{2, 3, 1, 1, 4};
    std::cout << j(nums) << std::endl;
    return 0;
}
