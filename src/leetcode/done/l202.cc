#include <iostream>
#include <map>
#include "gtest/gtest.h"

using namespace std;

namespace {
    bool IsHappyNumber(int n) {
        std::map<int, bool> visit;
        visit.insert(std::make_pair(n, true));
        std::map<int, bool>::iterator it;
        while (n != 1) {
            int next = 0;
            while (n != 0) {
                int x = (n % 10);
                next += (x * x);
                n /= 10;
            }
            n = next;
            if ((it = visit.find(n)) != visit.end()) return false;
            visit.insert(std::make_pair(n, true));
        }
        return true;
    }
} // anonymous namespace

TEST(IsHappyNumberTest, Case0) {
    ASSERT_FALSE(IsHappyNumber(2)); 
    // ASSERT_TRUE(IsHappyNumber(19)); 
    // ASSERT_TRUE(IsHappyNumber(1)); 
    // ASSERT_TRUE(IsHappyNumber(10)); 
    // ASSERT_TRUE(IsHappyNumber(100)); 
    // ASSERT_TRUE(IsHappyNumber(1000)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
