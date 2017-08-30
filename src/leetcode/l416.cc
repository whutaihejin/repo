#include <iostream>
#include <unordered_set>

#include <gtest/gtest.h>

using namespace std;

namespace {

    bool canPartition(vector<int>& nums) {
        if (nums.size() < 1U) return false;
        int sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) 
            sum += nums[i];
        if (sum % 2 == 1) return false;
        int target = sum / 2;
        std::unordered_set<int> set({0});
        for (size_t i = 0; i < nums.size(); ++i) {
            for (std::unordered_set<int>::iterator it = set.begin(); it != set.end(); ++it) {
                int val = nums[i] + *it;
                if (val == target) return true;
                else if (val < target) set.insert(val);
            }
        }
        return false;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums = {1, 2, 4, 5, 6};
    ASSERT_EQ(true, canPartition(nums)); 
}

TEST(YourTest, Case1) {
    std::vector<int> nums = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
    ASSERT_EQ(true, canPartition(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
