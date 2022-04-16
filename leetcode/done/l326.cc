#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  // max power of 3 is 3^19=1162261467 in int32_t 
  bool isPowerOfThree(int n) {
    const static int max_three_power = 1162261467;
    return n > 0 && max_three_power % n == 0;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
