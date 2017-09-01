#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  int missingNumber(vector<int>& nums) {
    int val = 0, n = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
      val ^= (nums[i] ^ n);
      n++;
    }
    return val ^ n;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
