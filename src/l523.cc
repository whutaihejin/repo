#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace {
     bool checkSubarraySum(vector<int>& nums, int k) {
         int size = nums.size();
         for (int low = 0; low < size; ++low) {
             int sum = nums[low];
             for (int high = low + 1; high < size; ++high) {
                 sum += nums[high];
                 if (k == 0) {
                     if (sum == 0) return true;
                 } else if (sum % k == 0) {
                     return true;
                 }
             }
         }
         return false;
     }
} // anonymous namespace

TEST(CheckSubarraySumTest, Case0) {
    int array[] = {23, 2, 4, 6, 7};
    std::vector<int> vec(&array[0], &array[4]);
    ASSERT_TRUE(checkSubarraySum(vec, 6)); 
}

TEST(CheckSubarraySumTest, Case1) {
    int array[] = {23, 2, 6, 4, 7};
    std::vector<int> vec(&array[0], &array[4]);
    ASSERT_TRUE(checkSubarraySum(vec, 6)); 
}

TEST(CheckSubarraySumTest, Case2) {
    std::vector<int> vec;
    ASSERT_FALSE(checkSubarraySum(vec, 6)); 
    vec.push_back(1);
    ASSERT_FALSE(checkSubarraySum(vec, 1)); 
}

TEST(CheckSubarraySumTest, Case3) {
    int array[] = {23, 2, 6, 4, 7};
    std::vector<int> vec(&array[0], &array[4]);
    ASSERT_FALSE(checkSubarraySum(vec, 0)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
