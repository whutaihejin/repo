#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int hammingWeight(uint32_t n) {
        n = ((n & 0xaaaaaaaa) >> 1) + (n & 0x55555555);
        n = ((n & 0xcccccccc) >> 2) + (n & 0x33333333);
        n = ((n & 0xf0f0f0f0) >> 4) + (n & 0x0f0f0f0f);
        n = ((n & 0xff00ff00) >> 8) + (n & 0x00ff00ff);
        n = ((n & 0xffff0000) >> 16) + (n & 0x0000ffff);
        return n;
    }
} // anonymous namespace

TEST(hammingWeightTest, Case0) {
    ASSERT_EQ(0, hammingWeight(0U)); 
    ASSERT_EQ(1, hammingWeight(1U)); 
    ASSERT_EQ(1, hammingWeight(2U)); 
    ASSERT_EQ(3, hammingWeight(11U)); 
    ASSERT_EQ(4, hammingWeight(0x0FU)); 
    ASSERT_EQ(32, hammingWeight(0xFFFFFFFFU)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
