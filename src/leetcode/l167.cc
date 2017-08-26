#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
  vector<int> twoSum(vector<int>& numbers, int target) {
      std::vector<int> ret;
      for (int low = 0, high = numbers.size() - 1; low < high;) {
          int sum = numbers[low] + numbers[high];
          if (sum < target) low++;
          else if (sum > target) high--;
          else {
            ret.push_back(low + 1);
            ret.push_back(high + 1);
            break;
          }
      }
      return ret;
  }
} // anonymous namespace

TEST(twoSumTest, Case0) {
    std::vector<int> nums = {2, 7, 11, 17};
    std::vector<int> ret = twoSum(nums, 9);
    ASSERT_EQ(2U, ret.size()); 
    ASSERT_EQ(1, ret[0]); 
    ASSERT_EQ(2, ret[1]); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
