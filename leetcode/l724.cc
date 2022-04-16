#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
	int pivotIndex(vector<int>& nums) {
        int sum = 0;
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            sum += *it;
        }
        int prefix_sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            prefix_sum += nums[i];
            if ((prefix_sum << 1) == sum + nums[i]) {
                return i;
            }
        }
        return -1;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
