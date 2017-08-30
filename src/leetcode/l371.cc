#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int add(int a, int b) {
        while (b) {
            int carry = (a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(-2, add(-1, -1)); 
    ASSERT_EQ(-1, add(-1, 0)); 
    ASSERT_EQ(2, add(-1, 3)); 
    ASSERT_EQ(-2, add(0, -2)); 
    ASSERT_EQ(0, add(0, 0)); 
    ASSERT_EQ(3, add(0, 3)); 
    ASSERT_EQ(1, add(2, -1)); 
    ASSERT_EQ(2, add(2, 0)); 
    ASSERT_EQ(5, add(2, 3)); 
    ASSERT_EQ(512, add(200, 312)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
