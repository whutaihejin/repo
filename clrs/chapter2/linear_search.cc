#include <iostream>
#include <vector>
#include <algorithm>

int LinearSearch(std::vector<int>& nums, int target) {
    int rst = -1;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) {
            rst = i;
            break;
        }
    }
    return rst;
}

int main() {
    std::vector<int> nums{31, 41, 59, 26, 41, 58};
    for_each(nums.begin(), nums.end(), [](const int& v) { std::cout << v << " "; });
    std::cout << std::endl;
    int rst = LinearSearch(nums, 22);
    std::cout << "Search result: " <<  rst << " for " << 22 << std::endl;
    rst = LinearSearch(nums, 41);
    std::cout << "Search result: " << rst << " for " << 41 << std::endl;
    return 0;
}
