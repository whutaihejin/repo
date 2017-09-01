#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  bool isPerfectSquare(int num) {
    if (num <= 0) return false;
    int64_t l = 1, h = num;
    while (l + 1 < h) {
      int64_t mid = (l + h) / 2;
      if (mid * mid == num) return true;
      if (mid * mid < num) l = mid;
      else h = mid;
    }
    return (l * l == num || h * h == num) ? true : false;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
