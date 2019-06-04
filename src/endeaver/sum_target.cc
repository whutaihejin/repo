#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int, int, int>> Sum3(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::tuple<int, int, int>> rst;
    int limit = nums.size(); // convert size_t to int for zero condition
    for (int k = 0; k < limit; k++) {
        for (int low = k + 1, high = limit - 1; low < high; ) {
            int sum = nums[low] + nums[high];
            if (sum < -nums[k]) {
                low++;
            } else if (sum > -nums[k]) {
                high--;
            } else {
                rst.push_back({nums[k], nums[low], nums[high]});
                int low_val = nums[low], high_val = nums[high];
                while (low < high && nums[low] == low_val) { low++; }
                while (low < high && nums[high] == high_val) { high--; }
            }
        }
        // move to next element which does not euqal the current value
        while (k + 1 < limit && nums[k + 1] == nums[k]) { k++; }
    }
    return rst;
}

int main() {
    // std::vector<int> nums{-2, -1, 0, 0, 1, 2};
    std::vector<int> nums{-1, 0, 1, 2, -1, -4};
    std::vector<std::tuple<int, int, int>> rst = Sum3(nums);
    for (auto it = rst.begin(); it != rst.end(); ++it) {
        std::cout << std::get<0>(*it) << " " << std::get<1>(*it) << " " << std::get<2>(*it) << std::endl;
    }
    return 0;
}
