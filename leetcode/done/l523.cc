#include <iostream>
#include <vector>
#include <map>
#include "gtest/gtest.h"

using namespace std;

namespace {
     bool checkSubarraySum(vector<int>& nums, int k) {
         int sum = 0, size = nums.size();
         std::map<int, int> hash;
         std::map<int, int>::iterator it;
         hash.insert(std::make_pair(0, -1));
         for (int i = 0; i < size; ++i) {
             sum += nums[i];
             if (k != 0) sum %= k;
             if ((it = hash.find(sum)) != hash.end()) {
                 if (i - it->second >= 2) return true;
             } else {
                 hash.insert(std::make_pair(sum, i));
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
    ASSERT_FALSE(checkSubarraySum(vec, 0)); 
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

TEST(CheckSubarraySumTest, Case4) {
    int array[] = {1,2,0,0,0,0,8};
    std::vector<int> vec(&array[0], &array[6]);
    ASSERT_TRUE(checkSubarraySum(vec, 6)); 
}

TEST(CheckSubarraySumTest, Case5) {
    int array[] = {0,0,0,0,0,0,0};
    std::vector<int> vec(&array[0], &array[6]);
    ASSERT_TRUE(checkSubarraySum(vec, 6)); 
}

TEST(CheckSubarraySumTest, Case6) {
    int array[] = {1,0,1,0,0,0,0};
    std::vector<int> vec(&array[0], &array[6]);
    ASSERT_TRUE(checkSubarraySum(vec, 6)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
