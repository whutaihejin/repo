#include <iostream>
#include <gtest/gtest.h>

#include "lib/util.h"

using namespace std;

namespace {
    vector<int> productExceptSelf(vector<int>& nums) {
        std::vector<int> result(nums.size());
        int val = 1;
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = val;
            val *= nums[i];
        }
        val = 1;
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] *= val;
            val *= nums[i];
        }
        return result;
    }
} // anonymous namespace

TEST(productExceptSelfTest, Case0) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> result = productExceptSelf(nums);
    ASSERT_TRUE(leetcode::Equal({120, 60, 40, 30, 24}, result)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
