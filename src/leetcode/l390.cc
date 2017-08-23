#include <iostream>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int lastRemaining(int n) {
        int step = 1;
        int head = 1, remain = n;
        int left = true;
        while (remain > 1) {
            if (left || remain % 2 == 1) {
                head += step;
            }
            remain /= 2;
            step *= 2;
            left = !left;
        }
        return head;
    }
} // anonymous namespace

TEST(LastRemainingTest, Case0) {
    ASSERT_EQ(1, lastRemaining(1));
    ASSERT_EQ(2, lastRemaining(2));
    ASSERT_EQ(2, lastRemaining(3));
    ASSERT_EQ(2, lastRemaining(4));
    ASSERT_EQ(2, lastRemaining(5));
    ASSERT_EQ(4, lastRemaining(6));
    ASSERT_EQ(4, lastRemaining(7));
    ASSERT_EQ(6, lastRemaining(9));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
