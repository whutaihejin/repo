#include <iostream>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace {
    bool checkRecord(string s) {
        int late = 0, absent = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'A') absent++;
            if (s[i] == 'L') late++;
            else late = 0;
            if (late > 2 || absent > 1) return false;
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
    std::string record = "PLLPLLALLL";
    ASSERT_FALSE(checkRecord(record));
    
    record = "PLLPLLALL";
    ASSERT_TRUE(checkRecord(record));
}

TEST(CheckRecordTest, Case3) {
    std::string record = "PPAALLLL";
    ASSERT_FALSE(checkRecord(record));
}

TEST(CheckRecordTest, Case4) {
    std::string record = "PPPPP";
    ASSERT_TRUE(checkRecord(record));
}

TEST(CheckRecordTest, Case5) {
    std::string record = "LALL";
    ASSERT_TRUE(checkRecord(record));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
