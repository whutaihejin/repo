#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int linearMin(vector<int>& nums) {
        int min_val = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
           min_val = std::min(min_val, nums[i]); 
        }
        return min_val;
    }
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low + 1 < high) {
            int mid = low + (high - low) / 2;
            if (nums[low] < nums[mid]) {
                if (nums[mid] <= nums[high]) {
                    high = mid;
                } else {
                    low = mid;
                }
            } else if (nums[mid] == nums[high]) {
                if (nums[mid] < nums[high]) {
                    high = mid;
                } else if (nums[mid] == nums[high]) {
                    return linearMin(nums);
                } else {
                    low = mid;
                }
            } else {
                if (nums[mid] <= nums[high]) {
                    high = mid;
                } else { 
                    low = mid;
                }
            }
        }
        return nums[low] < nums[high] ? nums[low] : nums[high];
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums = {3, 0, 1, 1, 3};
    ASSERT_EQ(0, findMin(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
