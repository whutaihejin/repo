#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int doRob(vector<int>& nums, size_t index) {
        if (index >= nums.size()) return 0;
        return nums[index] + std::max(doRob(nums, index + 2), doRob(nums, index + 3));
    }
    int rob(vector<int>& nums) {
        return std::max(doRob(nums, 0), doRob(nums, 1));
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums;
    ASSERT_EQ(0, rob(nums)); 
   
    // 1
    nums.push_back(1);
    ASSERT_EQ(1, rob(nums)); 
   
    // 1, 2
    nums.push_back(2);
    ASSERT_EQ(2, rob(nums)); 
   
    // 1, 2, 3
    nums.push_back(3);
    ASSERT_EQ(4, rob(nums)); 
}

TEST(YourTest, Case1) {
    std::vector<int> nums;
    // 2, 1, 1, 2
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    ASSERT_EQ(4, rob(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
