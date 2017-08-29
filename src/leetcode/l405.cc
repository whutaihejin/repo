#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

namespace {
  string toHex(int num) {
    if (num == 0) return "0";
    string ret;
    unsigned int x = num;
    while (x != 0) {
      int val = x % 16;
      ret.push_back(val + (val > 9 ? 'a' - 10 : '0'));
      x /= 16;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
