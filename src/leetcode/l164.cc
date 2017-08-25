#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    // version of time limit exceeded
    int maximumGap(vector<int>& nums) {
        int maxv = 0;
        std::set<int> repo;
        for (size_t i = 0; i < nums.size(); ++i) {
            maxv = std::max(nums[i], maxv);
            repo.insert(nums[i]);
        }
        int gap = 0;
        std::set<int>::iterator it;
        for (int i = maxv - 1; i >= 0; --i) {
            if ((it = repo.find(i)) != repo.end()) {
                gap = std::max(maxv - i, gap);
                maxv = i;
            }
        }
        return gap;
    }
} // anonymous namespace

TEST(maximumGapTest, Case0) {
    std::vector<int> nums;
    ASSERT_EQ(0, maximumGap(nums)); 
    nums.push_back(1);
    ASSERT_EQ(0, maximumGap(nums)); 
    nums.push_back(9);
    ASSERT_EQ(8, maximumGap(nums)); 
}

TEST(maximumGapTest, Case1) {
    std::vector<int> nums = {7, 1, 6, 5};
    ASSERT_EQ(4, maximumGap(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
