#include <iostream>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

namespace {
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_map<int, int> map;
    for (size_t i = 0; i < nums1.size(); ++i) {
      if (map.count(nums1[i]) > 0) map[nums1[i]]++;
      else map[nums1[i]] = 1;
    }
    std::vector<int> vec;
    for (size_t i = 0; i < nums2.size(); ++i) {
      if (map.count(nums2[i]) > 0 && map[nums2[i]]-- > 0) {
        vec.push_back(nums2[i]);
      }
    }
    return vec;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
