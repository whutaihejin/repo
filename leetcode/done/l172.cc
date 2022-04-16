#include <iostream>
#include <stdint.h>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int trailingZeroes(int n) {
      if (n <= 1) return 0;
      int64_t count = 0;
      for (int64_t limit = 5; n >= limit; limit *= 5) {
          count += n / limit;
      }
      return count;
    }
} // anonymous namespace

TEST(trailingZeroesTest, Case0) {
    ASSERT_EQ(49, trailingZeroes(200)); 
    ASSERT_EQ(0, trailingZeroes(-3)); 
    ASSERT_EQ(0, trailingZeroes(-1)); 
    ASSERT_EQ(0, trailingZeroes(0)); 
    ASSERT_EQ(0, trailingZeroes(1)); 
    ASSERT_EQ(0, trailingZeroes(2)); 
    ASSERT_EQ(1, trailingZeroes(5)); 
    ASSERT_EQ(2, trailingZeroes(10)); 
    ASSERT_EQ(6, trailingZeroes(25)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
