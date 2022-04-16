#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  char findTheDifference(string s, string t) {
    size_t i = 0, limit = s.size() < t.size() ? s.size() : t.size();
    char val = 0;
    for (; i < limit; ++i) {
      val ^= s[i];
      val ^= t[i];
    }
    if (i < s.size()) val ^= s[i];
    if (i < t.size()) val ^= t[i];
    return val;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
