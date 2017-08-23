#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    // do reverse of version v1
    uint32_t doReverseBits_v1(uint32_t n) {
        uint32_t val = 0x00;
        for (int i = 0; i < 32; ++i) {
            val |= (((n >> i) & 0x01) << (31 -i));
        }
        return val;        
    }
    
    // do reverse of version v2
    uint32_t doReverseBits_v2(uint32_t n) {
        n = (n << 16) | (n >> 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }

    // interface
    uint32_t reverseBits(uint32_t n) {
        return doReverseBits_v2(n);
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
