#include <iostream>
#include "gtest/gtest.h"
#include <vector>

using namespace std;

namespace {

    int findPeakElement(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (nums[mid] < nums[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

} // anonymous namespace

TEST(findPeakElementTest, Case0) {
    vector<int> nums;
    ASSERT_EQ(0, findPeakElement(nums));
    nums.push_back(1);
    ASSERT_EQ(0, findPeakElement(nums));
    nums.push_back(2);
    ASSERT_EQ(1, findPeakElement(nums));
}

TEST(findPeakElementTest, Case1) {
    vector<int> nums = {2, 1};
    ASSERT_EQ(0, findPeakElement(nums));
    vector<int> n2 = {3, 2, 1};
    ASSERT_EQ(0, findPeakElement(n2));
}

TEST(findPeakElementTest, Case2) {
    vector<int> nums = {4, 3, 2, 1};
    ASSERT_EQ(0, findPeakElement(nums));
    vector<int> arr = {1, 2, 3, 4, 5};
    ASSERT_EQ(4, findPeakElement(arr));
    vector<int> arr2 = {1, 2, 3, 1};
    ASSERT_EQ(2, findPeakElement(arr2));
}

TEST(findPeakElementTest, Case3) {
    vector<int> n1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQ(0, findPeakElement(n1));
    vector<int> n2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(8, findPeakElement(n2));
    vector<int> n3 = {1, 3, 6, 2, 1, 2, 5, 3, 2};
    ASSERT_EQ(6, findPeakElement(n3));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
