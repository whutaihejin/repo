#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int rob(vector<int>& nums) {
        int value, max = 0;
        int pre = 0, cur = 0, next = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            value = nums[i] + std::max(pre, cur);
            max = std::max(max, value);
            pre = cur;
            cur = next;
            next = value;
        }
        return max;
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

TEST(YourTest, Case2) {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(1);
    ASSERT_EQ(3, rob(nums)); 
}

TEST(YourTest, Case3) {
    std::vector<int> nums;
    nums.push_back(2);
    nums.push_back(1);
    ASSERT_EQ(2, rob(nums)); 
}

TEST(YourTest, Case4) {
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    ASSERT_EQ(2, rob(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
