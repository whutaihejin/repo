#include <iostream>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

namespace {
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_map<int, int> map;
    std::unordered_map<int, int> rmap;
    for (size_t i = 0; i < nums1.size(); ++i) {
      map[nums1[i]] = 1;
    }
    for (size_t i = 0; i < nums2.size(); ++i) {
      if (map.count(nums2[i]) > 0) {
        rmap[nums2[i]] = 1;
      }
    }
    std::vector<int> vec;
    std::unordered_map<int, int>::iterator it;
    for (it = rmap.begin(); it != rmap.end(); ++it) {
      vec.push_back(it->first);
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
