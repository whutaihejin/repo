#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>

using namespace std;

namespace {
    bool compare(const std::string& v1, const std::string& v2) {
        std::string x = v1 + v2;
        std::string y = v2 + v1;
        return x > y ? true : false;
    }

    string largestNumber(vector<int>& nums) {
        std::string max;
        if (nums.empty()) return max;
        std::vector<std::string> vec;
        for (size_t i = 0; i < nums.size(); ++i) {
            vec.push_back(to_string(nums[i]));
        }
        std::stable_sort(vec.begin(), vec.end(), compare);
        bool first = true;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (first && vec[i] == "0") continue;
            first = false;
            max += vec[i];
        }
        return max.empty() ? "0" : max;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> vec = {3, 30, 34, 5, 9};
    ASSERT_EQ("9534330", largestNumber(vec)); 
    
    std::vector<int> v = {0, 0, 0};
    ASSERT_EQ("0", largestNumber(v)); 
}

TEST(YourTest, Case1) {
    std::vector<int> vec = {12, 121};
    ASSERT_EQ("12121", largestNumber(vec)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
