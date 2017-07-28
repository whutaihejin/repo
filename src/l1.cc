#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> index_list;
    return index_list;
}

TEST(TwoSumTest, TestNowWithArg) {
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    vector<int> index_list = twoSum(nums, 9);
    EXPECT_EQ(2U, index_list.size());
    EXPECT_EQ(0, index_list[0]);
    EXPECT_EQ(1, index_list[1]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}