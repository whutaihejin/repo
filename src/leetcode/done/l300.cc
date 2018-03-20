// 300. Longest Increasing Subsequence
// Given an unsorted array of integers, find the length of longest increasing subsequence.
// 
// For example,
//     Given [10, 9, 2, 5, 3, 7, 101, 18],
//     The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.
// 
//     Your algorithm should run in O(n2) complexity.
// 
//     Follow up: Could you improve it to O(n log n) time complexity?
//

#include <iostream>
#include <vector>
#include <gtest/gtest.h>
namespace {
    int lengthOfLIS(std::vector<int>& nums) {
        int max_len = 0;
        std::vector<int> lis(nums.size());
        for (size_t i = 0; i < nums.size(); ++i) {
            int len = 1;
            for (size_t j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    len = std::max(len, lis[j] + 1);
                }
            }
            lis[i] = len;
            max_len = std::max(max_len, len);
        }
        return max_len;
    }
} // namespace

TEST(LISTest, Case0) {
    std::vector<int> vec{10, 9, 2, 5, 3, 7, 101, 18};
    int length = lengthOfLIS(vec);
    ASSERT_EQ(4, length); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
