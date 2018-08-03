#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {

    string largestNumber(vector<int>& nums) {
        std::vector<std::string> vec;
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            vec.push_back(std::to_string(*it));
        }
        std::sort(vec.begin(), vec.end(), [](const std::string& x, const std::string& y) { return (x + y) > (y + x); });
        // case of all zero
        if (!vec.empty() && vec[0] == "0") {
            return "0";
        }
        // build result
        std::string result;
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            result.append(*it);
        }
        return result;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> nums;
    ASSERT_STREQ("", largestNumber(nums).c_str());
}

TEST(YourTest, Case1) {
    std::vector<int> nums{1};
    ASSERT_STREQ("1", largestNumber(nums).c_str());
}

TEST(YourTest, Case2) {
    std::vector<int> nums{3, 30};
    ASSERT_STREQ("330", largestNumber(nums).c_str());
}

TEST(YourTest, Case3) {
    std::vector<int> nums{3, 30, 34};
    ASSERT_STREQ("34330", largestNumber(nums).c_str());
}

TEST(YourTest, Case4) {
    std::vector<int> nums{3, 30, 34, 5, 9};
    ASSERT_STREQ("9534330", largestNumber(nums).c_str());
}

TEST(YourTest, Case5) {
    std::vector<int> nums{2, 10};
    ASSERT_STREQ("210", largestNumber(nums).c_str());
}

TEST(YourTest, Case6) {
    std::vector<int> nums{0, 0, 0};
    ASSERT_STREQ("0", largestNumber(nums).c_str());
}

TEST(YourTest, Case7) {
    std::vector<int> nums{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    ASSERT_STREQ("0", largestNumber(nums).c_str());
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
