#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  int addDigits(int num) {
    while (num > 9) {
      int x = 0;
      while (num > 0) {
        x += num % 10;
        num /= 10;
      }
      num = x;
    }
    return num;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
