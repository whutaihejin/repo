#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    class NumArray {
        public:
            NumArray(vector<int> nums) {
                int val = 0;
                for (size_t i = 0; i < nums.size(); ++i) {
                    sum_.push_back(val);
                    val += nums[i];
                }
                sum_.push_back(val);
            }

            int sumRange(int i, int j) {
                return sum_[j + 1] - sum_[i];
            }
        private:
            // sum of nums
            std::vector<int> sum_;
    };
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
