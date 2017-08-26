#include <iostream>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int majorityElement(vector<int>& nums) {
        std::unordered_map<int, int> map;
        std::unordered_map<int, int>::iterator it;
        for (size_t i = 0; i < nums.size(); ++i) {
            if ((it = map.find(nums[i])) != map.end()) {
                it->second++;
            } else {
                map[nums[i]] = 1;
            }
        }
        int threshold = nums.size() / 2;
        for (it = map.begin(); it != map.end(); ++it) {
            if (it->second > threshold) return it->first;
        }
        return -1;
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
