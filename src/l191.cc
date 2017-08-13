#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int hammingWeight(uint32_t n) {
        int weight = 0;
        while (n != 0) {
            weight += ((n & 0x01) == 0 ? 0 : 1);
            n >>= 1;
        }
        return weight;          
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
