#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    vector<int> singleNumber(vector<int>& nums) {
        int xor_val = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            xor_val ^= nums[i];
        }
        int xor_x = 0, xor_y = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if ((nums[i] ^ xor_val) > nums[i]) {
                xor_x ^= nums[i];
            } else {
                xor_y ^= nums[i];
            }
        }
        std::vector<int> result;
        result.push_back(xor_x);
        result.push_back(xor_y);
        std::sort(result.begin(), result.end());
        return result;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 5};
    std::vector<int> result = singleNumber(nums);
    ASSERT_EQ(2U, result.size()); 
    ASSERT_EQ(2, result[0]); 
    ASSERT_EQ(5, result[1]); 
}

TEST(YourTest, Case1) {
    std::vector<int> nums = {2, 5};
    std::vector<int> result = singleNumber(nums);
    ASSERT_EQ(2U, result.size()); 
    ASSERT_EQ(2, result[0]); 
    ASSERT_EQ(5, result[1]); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
