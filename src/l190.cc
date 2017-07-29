#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    uint32_t reverseBits(uint32_t n) {
        uint32_t val = 0x00;
        for (int i = 0; i < 32; ++i) {
            val |= (((n >> i) & 0x01) << (31 -i));
        }
        return val;        
    }
} // anonymous namespace

TEST(ReverseBitsTest, Case0) {
    ASSERT_EQ(0U, reverseBits(0));
    ASSERT_EQ(0xFFFFFFFFU, reverseBits(0xFFFFFFFF));
    ASSERT_EQ(0x80000000U, reverseBits(0x01));
    ASSERT_EQ(0x01U, reverseBits(0x80000000));
    ASSERT_EQ(964176192U, reverseBits(43261596));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
