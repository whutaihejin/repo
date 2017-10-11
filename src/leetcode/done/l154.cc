#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] < nums[high]) {
                high = mid;
            } else if (nums[mid] > nums[high]) {
                low = mid + 1;
            } else {
                high--;
            }
        }
        return nums[low];
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
