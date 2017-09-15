#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    bool isBadVersion(int version) {
        return version >= 10 ? true : false;
    }

    int firstBadVersion(int n) {
        int l = 1, h = n;
        while (l + 1 < h) {
            int mid = l + (h - l) / 2;
            if (isBadVersion(mid)) {
                h = mid;
            } else {
                l = mid;
            }
        }
        return isBadVersion(l) ? l : h;
    }
} // anonymous namespace

TEST(firstBadVersionTest, Case0) {
    ASSERT_EQ(10, firstBadVersion(100)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
