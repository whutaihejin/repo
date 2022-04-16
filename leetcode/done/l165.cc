#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int getToken(std::string& version, size_t& index) {
        int ver = 0;
        for (; index < version.size(); ++index) {
            char ch = version[index];
            if (ch == '.') {
                index++;
                break;
            }
            ver = ver * 10 + ch - '0';
        }
        return ver;
    }

    int compareVersion(std::string version1, std::string version2) {
        size_t idx1 = 0, idx2 = 0;
        int v1 = 0, v2 = 0;
        while (idx1 < version1.size() && idx2 < version2.size()) {
            v1 = getToken(version1, idx1);
            v2 = getToken(version2, idx2);
            if (v1 < v2) return -1;
            else if (v1 > v2) return 1;
        }
        while (idx1 < version1.size()) {
            if (getToken(version1, idx1) != 0) return 1;
        }
        while (idx2 < version2.size()) {
            if (getToken(version2, idx2) != 0) return -1;
        }
        return 0;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(1, compareVersion("1.12", "1.11")); 
    ASSERT_EQ(0, compareVersion("1.11", "1.11")); 
    ASSERT_EQ(-1, compareVersion("1.11", "1.12")); 
    ASSERT_EQ(-1, compareVersion("0.1", "1.1")); 
    ASSERT_EQ(1, compareVersion("1.1", "0.1")); 
    ASSERT_EQ(-1, compareVersion("1.1", "13.37")); 
    ASSERT_EQ(1, compareVersion("13.37", "1.2")); 
    ASSERT_EQ(1, compareVersion("13.", "1.2")); 
    ASSERT_EQ(-1, compareVersion(".12", "0.22")); 
    ASSERT_EQ(1, compareVersion("0.22", ".12")); 
    ASSERT_EQ(-1, compareVersion("1", "1.1")); 
    ASSERT_EQ(1, compareVersion("1.1", "1")); 
    ASSERT_EQ(0, compareVersion("1.0", "1")); 
    ASSERT_EQ(0, compareVersion("1", "1.0")); 
    ASSERT_EQ(-1, compareVersion("1", "1.0.1")); 
    ASSERT_EQ(1, compareVersion("1.0.1", "1")); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
