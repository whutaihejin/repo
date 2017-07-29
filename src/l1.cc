#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "gtest/gtest.h"

using namespace std;

namespace {
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> index_list;
        std::map<int, int> hash;
        std::map<int, int>::iterator it;
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            int key = nums[i];
            if ((it = hash.find(key)) != hash.end()) {
                index_list.push_back(it->second);
                index_list.push_back(i);
                break;
            } else {
                hash.insert(std::make_pair(target - key, i));
            }
        }
        return index_list;
    }
} // anonymous namespace

TEST(TwoSumTest, Case0) {
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    vector<int> index_list = twoSum(nums, 9);
    ASSERT_EQ(2U, index_list.size());
    EXPECT_EQ(0, index_list[0]);
    EXPECT_EQ(1, index_list[1]);
}

TEST(TwoSumTest, Case1) {
    vector<int> nums;
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(5);
    nums.push_back(15);
    vector<int> index_list = twoSum(nums, 10);
    ASSERT_EQ(2U, index_list.size());
    EXPECT_EQ(0, index_list[0]);
    EXPECT_EQ(2, index_list[1]);
}

TEST(TwoSumTest, Case2) {
    vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(4);
    vector<int> index_list = twoSum(nums, 6);
    ASSERT_EQ(2U, index_list.size());
    EXPECT_EQ(1, index_list[0]);
    EXPECT_EQ(2, index_list[1]);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
