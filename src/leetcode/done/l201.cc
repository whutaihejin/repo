#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    int rangeBitwiseAnd(int m, int n) {
        if (m == 0) {
            return 0;
        }
        int factor = 0;
        while (m != n) {
            m >>= 1;
            n >>= 1;
            factor++;
        }
        return m << factor;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(4, rangeBitwiseAnd(4, 7)); 
    ASSERT_EQ(0, rangeBitwiseAnd(0, 7)); 
    ASSERT_EQ(8, rangeBitwiseAnd(8, 9)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
