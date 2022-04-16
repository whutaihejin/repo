#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  int thirdMax(vector<int>& nums) {
    int max = nums[0], second = -1, third = -1;
    bool second_flag = false, third_flag = false;
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == max) continue;
      else if (nums[i] > max) {
        if (!second_flag) second_flag = true;
        else { third_flag = true; third = second; }
        second = max;
        max = nums[i];
      } else {
        if (!second_flag) { second_flag = true; second = nums[i]; } 
        else {
          if (nums[i] == second) continue;
          else if (nums[i] > second) {           
            third_flag = true;
            third = second;
            second = nums[i];
          } else {
            if (!third_flag || nums[i] > third) {
              third_flag = true; third = nums[i];
            }
          }
        }
      }
    }
    return third_flag ? third : max;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
