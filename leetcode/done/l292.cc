#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_FALSE(canWinNim(0)); 
    ASSERT_TRUE(canWinNim(1)); 
    ASSERT_TRUE(canWinNim(2)); 
    ASSERT_TRUE(canWinNim(3)); 
    ASSERT_FALSE(canWinNim(4)); 
    ASSERT_TRUE(canWinNim(5)); 
    ASSERT_TRUE(canWinNim(6)); 
    ASSERT_TRUE(canWinNim(7)); 
    ASSERT_FALSE(canWinNim(8)); 
    ASSERT_TRUE(canWinNim(9)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
