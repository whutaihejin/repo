#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    vector<string> summaryRanges(vector<int>& nums) {
        // 利用两个下标指针low/high进行边界标识，初始low为0，high初始为low + 1
        // high向后走直到遇到和前一个差值大于1的时候终止；判断low和high - 1的值，
        // 相同说明此区间只有一个数, 负责为[low, high - 1]; 下一轮low = high - 1，依次类推。
        std::vector<std::string> result;
        for (size_t low = 0; low < nums.size();) {
            size_t high = low + 1;
            while (nums[high] - nums[high - 1] == 1) {
                high++;
            }
            if (low == high - 1) {
                result.push_back(std::to_string(nums[low]));
            } else {
                result.push_back(std::to_string(nums[low]) + "->" + std::to_string(nums[high - 1]));
            }
            low = high;
        }
        return result;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
