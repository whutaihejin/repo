#include <iostream>
#include <vector>

int MaxProfit(std::vector<int>& nums) {
    int profit = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            profit = std::max(profit, nums[j] - nums[i]);
        }
    }
    return profit;
}

int main() {
    std::vector<int> nums{100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
    int profit = MaxProfit(nums);
    std::cout << "profit: " << profit << std::endl;
    return 0;
}
