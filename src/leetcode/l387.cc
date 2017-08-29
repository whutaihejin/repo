#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  int firstUniqChar(string s) {
    const int size = 256;
    int map[256] = {0};
    for (size_t i = 0; i < s.size(); ++i) {
      map[s[i]]++;
    }
    for (size_t i = 0; i < s.size(); ++i) {
      if (map[s[i]] == 1) return i;
    }
    return -1;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
