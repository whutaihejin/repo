#include <iostream>
#include <vector>
#include <map>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int total = 0, size = timeSeries.size();
        int low = -1, high = -1;
        for (int i = 0; i < size; ++i) {
            int t = timeSeries[i];
            if (t > high) {
                total += high - low;
                low = t;
                high = low + duration;
            } else {
                high = t + duration;
            }
        }
        total += high - low;
        return total;
    }
} // anonymous namespace

TEST(TwoSumTest, Case0) {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(4);
    ASSERT_EQ(4, findPoisonedDuration(nums, 2));
}

TEST(TwoSumTest, Case1) {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    ASSERT_EQ(3, findPoisonedDuration(nums, 2));
}

TEST(TwoSumTest, Case2) {
    vector<int> nums;
    ASSERT_EQ(0, findPoisonedDuration(nums, 2));
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(6);
    ASSERT_EQ(7, findPoisonedDuration(nums, 2));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
