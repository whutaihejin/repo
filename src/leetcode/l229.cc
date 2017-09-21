#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result;
        int candidatex = 0, countx = 0;
        int candidatey = 0, county = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (countx == 0) {
                countx++;
                candidatex = nums[i];
            } else if (candidatex == nums[i]) {
                countx++;
            } else if (county == 0) {
                county++;
                candidatey = nums[i];
            } else if (candidatey == nums[i]) {
                county++;
            } else {
                countx--;
                county--;
            }
        }
        size_t x = 0, y = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (countx > 0 && nums[i] == candidatex) x++;
            if (county > 0 && nums[i] == candidatey) y++;
        }
        if (x > nums.size() / 3) result.push_back(candidatex);
        if (y > nums.size() / 3) result.push_back(candidatey);
        return result;
    }
} // anonymous namespace

TEST(majorityElementTest, Case0) {
    std::vector<int> v = {0, 0, 0};
    std::vector<int> r = majorityElement(v);
    ASSERT_EQ(1U, r.size()); 
    ASSERT_EQ(0, r[0]); 
}

TEST(majorityElementTest, Case1) {
    std::vector<int> v = {1, 3, 3, 4};
    std::vector<int> r = majorityElement(v);
    ASSERT_EQ(1U, r.size()); 
    ASSERT_EQ(3, r[0]); 
}

TEST(majorityElementTest, Case2) {
    std::vector<int> v = {-1,1,1,1,2,1};
    std::vector<int> r = majorityElement(v);
    ASSERT_EQ(1U, r.size()); 
    ASSERT_EQ(1, r[0]); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
