#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

namespace {
    string convertToTitle(int n) {
        std::string title;
        for (int r; n > 0;) {
            r = n % 26;
            n /= 26;
            if (r == 0) {
                r = 26;
                n -= 1;
            }
            title.push_back(r - 1 + 'A');
        }
        std::reverse(title.begin(), title.end());
        return title;
    }
    int reverseTitle(std::string title) {
        int val = 0;
        for (size_t i = 0; i < title.size(); ++i) {
            val = val * 26 + (title[i] - 'A' + 1);
        }
        return val;
    }
} // anonymous namespace

TEST(convertToTitleTest, Case0) {
    ASSERT_EQ("A", convertToTitle(1)); 
    ASSERT_EQ("B", convertToTitle(2)); 
    ASSERT_EQ("C", convertToTitle(3)); 
    ASSERT_EQ("Y", convertToTitle(25)); 
    ASSERT_EQ("Z", convertToTitle(26)); 
    ASSERT_EQ("AA", convertToTitle(27)); 
    ASSERT_EQ("AB", convertToTitle(28)); 
    for (int i = 29; i <= 10000; ++i) {
        ASSERT_EQ(i, reverseTitle(convertToTitle(i))); 
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
