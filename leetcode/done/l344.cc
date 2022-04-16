#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  string reverseString(string s) {
    char ch;
    for (int l = 0, h = s.size() - 1; l < h; l++, h--) {
      ch = s[l];
      s[l] = s[h];
      s[h] = ch;
    }
    return s;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
