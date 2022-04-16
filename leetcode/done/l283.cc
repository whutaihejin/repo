#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  void moveZeroes(vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        size_t j = i + 1;
        while (j < nums.size() && nums[j] == 0) j++;
        if (j < nums.size()) {
          int tmp = nums[i];
          nums[i] = nums[j];
          nums[j] = tmp;
        }
      }
    }
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
