#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    bool walk(vector<int>& nums, size_t index, int pick, int sum) {
        if (index >= nums.size()) return pick == sum;
        //if (pick == sum) return true;
        // else if (pick > sum) return false;
        if (walk(nums, index + 1, pick + nums[index], sum)) return true;
        return walk(nums, index + 1, pick, sum); 
    }

    bool canPartition(vector<int>& nums) {
        if (nums.size() < 1U) return false;
        int sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) 
            sum += nums[i];
        if (sum % 2 == 1) return false;
        return walk(nums, 0, 0, sum / 2);
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
    ASSERT_EQ(true, canPartition(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
