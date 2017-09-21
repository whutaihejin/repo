#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int major = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (count == 0) {
                count++;
                major = nums[i];
            } else if (major == nums[i]) {
                count++;
            } else {
                count--;
            }
        }
        return major;
    }
} // anonymous namespace

TEST(majorityElementTest, Case0) {
    std::vector<int> nums = {1};
    ASSERT_EQ(1, majorityElement(nums)); 
}

TEST(majorityElementTest, Case1) {
    std::vector<int> n1 = {1, 1};
    ASSERT_EQ(1, majorityElement(n1)); 
    std::vector<int> nums = {1, 2, 2};
    ASSERT_EQ(2, majorityElement(nums)); 
}

TEST(majorityElementTest, Case2) {
    std::vector<int> nums = {1, 2, 2, 2};
    ASSERT_EQ(2, majorityElement(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
