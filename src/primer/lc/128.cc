#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int longestConsecutive(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    int rst = 0;
    for (int i = 0; i < nums.size(); ) {
        int j = i + 1;
        while (j < nums.size() && nums[j] == nums[j - 1] + 1) j++;
        rst = max(rst, j - i);
        i = j;
    }
    return rst;
}

int main() {
    std::vector<int> nums{100,4, 200, 1,3,2};
    int r = longestConsecutive(nums);
    assert(4 == r);
    return 0;
}
