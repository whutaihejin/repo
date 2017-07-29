#include <iostream>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace {
    bool checkRecord(string s) {
        int size = s.size();
        int late = 0, absent = 0;
        for (int i = 0; i < size; ++i) {
            char ch = s[i];
            if (ch == 'P') {
                continue;
            } else if (ch == 'L') {
                if (++late > 2) {
                    return false;
                }
            } else if (++absent > 1) {
                return false;
            }
        }
        return true;
    }
} // anonymous namespace

TEST(CheckRecordTest, Case0) {
    std::string record = "PPALLP";
    ASSERT_TRUE(checkRecord(record));
}

TEST(CheckRecordTest, Case1) {
    std::string record = "PPALLL";
    ASSERT_FALSE(checkRecord(record));
}

TEST(CheckRecordTest, Case2) {
    std::string record = "PPAAL";
    ASSERT_FALSE(checkRecord(record));
}

TEST(CheckRecordTest, Case3) {
    std::string record = "PPAALLLL";
    ASSERT_FALSE(checkRecord(record));
}

TEST(CheckRecordTest, Case4) {
    std::string record = "PPPPP";
    ASSERT_TRUE(checkRecord(record));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
