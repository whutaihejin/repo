#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  bool isUgly(int num) {
      if (num < 1) return false;
      while (num > 1) {
        if (num % 5 == 0) {
          num /= 5; continue;
        }
        if (num % 3 == 0) {
          num /= 3; continue;
        }
        if (num % 2 == 0) {
          num /= 2; continue;
        }
        break;
      }
      return num == 1 ? true : false;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_FALSE(isUgly(-6)); 
    ASSERT_FALSE(isUgly(-1)); 
    ASSERT_FALSE(isUgly(0)); 
    ASSERT_TRUE(isUgly(1)); 
    ASSERT_TRUE(isUgly(2)); 
    ASSERT_TRUE(isUgly(3)); 
    ASSERT_TRUE(isUgly(4)); 
    ASSERT_TRUE(isUgly(5)); 
    ASSERT_TRUE(isUgly(6)); 
    ASSERT_FALSE(isUgly(7)); 
    ASSERT_TRUE(isUgly(8)); 
    ASSERT_TRUE(isUgly(9)); 
    ASSERT_TRUE(isUgly(10)); 
    ASSERT_FALSE(isUgly(11)); 
    ASSERT_TRUE(isUgly(12)); 
    ASSERT_FALSE(isUgly(13)); 
    ASSERT_FALSE(isUgly(14)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
