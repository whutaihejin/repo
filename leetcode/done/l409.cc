#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  int longestPalindrome(string s) {
    const int size = 256;
    int map[size] = {0};
    for (size_t i = 0; i < s.size(); ++i) {
      map[s[i]]++;
    }
    int count = 0, odd = 0;
    for (int i = 0; i < size; ++i) {
      if (map[i] % 2 == 0) {
        count += map[i];
      } else {
        odd = 1;
        count += std::max(0, map[i] - 1);
      }
    }
    if (odd) count++;
    return count;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
