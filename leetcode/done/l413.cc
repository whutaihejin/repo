#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int numberOfArithmeticSlices(vector<int>& A) {
        if (A.size() < 3) return 0;
        vector<int> dp(A.size(), 0);
        int count = 0;
        for (size_t i = 2; i < dp.size(); ++i) {
          if (A[i] + A[i - 2] == (A[i - 1] << 1)) {
            dp[i] = dp[i - 1] + 1;
          }
          count += dp[i];
        }
        return count;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    vector<int> nums = {1, 2, 3, 4};
    ASSERT_EQ(3, numberOfArithmeticSlices(nums)); 
}

TEST(YourTest, Case1) {
    vector<int> nums = {1, 1, 2, 5, 7};
    ASSERT_EQ(0, numberOfArithmeticSlices(nums)); 
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
