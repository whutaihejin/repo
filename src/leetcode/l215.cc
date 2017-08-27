#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int findKthLargest(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> vec = {1, 3, 5, 5, 6};
    ASSERT_EQ(5, findKthLargest(vec, 2)); 
    ASSERT_EQ(6, findKthLargest(vec, 1)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
