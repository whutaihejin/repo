#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    void reverse(vector<int>& nums, int l, int h) {
        for (; l < h; l++, h--) {
            nums[l] = nums[l] ^ nums[h];
            nums[h] = nums[l] ^ nums[h];
            nums[l] = nums[l] ^ nums[h];
        }
    }

    void rotate(vector<int>& nums, int k) {
        if (nums.empty()) return;
        int size = nums.size();
        if ((k %= size) == 0) return;
        reverse(nums, 0, size - k - 1);
        reverse(nums, size - k, size - 1);
        reverse(nums, 0, size - 1);
    }

    std::string toString(std::vector<int>& nums) {
        std::string arr;
        std::string sep = "";
        for (size_t i = 0; i < nums.size(); ++i) {
            arr += sep + to_string(nums[i]);
            sep = ",";
        }
        return arr;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> vec;
    rotate(vec, 1);
    ASSERT_EQ("", toString(vec)); 

    vec.push_back(1);
    rotate(vec, 1);
    ASSERT_EQ("1", toString(vec)); 
    
    vec.push_back(2);
    rotate(vec, 1);
    ASSERT_EQ("2,1", toString(vec)); 
}

TEST(YourTest, Case1) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    rotate(vec, 3);
    ASSERT_EQ("4,5,6,7,1,2,3", toString(vec)); 
    rotate(vec, 4);
    ASSERT_EQ("1,2,3,4,5,6,7", toString(vec)); 
    rotate(vec, 7);
    ASSERT_EQ("1,2,3,4,5,6,7", toString(vec)); 
    rotate(vec, 0);
    ASSERT_EQ("1,2,3,4,5,6,7", toString(vec)); 
    rotate(vec, 8);
    ASSERT_EQ("2,3,4,5,6,7,1", toString(vec)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
