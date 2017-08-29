#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
    int numberOfArithmeticSlices(vector<int>& A) {
        if (A.size() < 3) return 0;
        vector<int> row(A.size());
        vector<vector<int>> matrix(A.size(), row);
        // init
        for (size_t i = 1; i < A.size(); ++i) {
            matrix[i - 1][i] = 1;
        }
        int count = 0;
        for (size_t len = 3; len <= A.size(); ++len) {
            for (size_t i = 0; i <= A.size() - len; ++i) {
                int j = i + len - 1;
                if (matrix[i][j - 1] && (A[i] + A[j - 1] == (A[j] << 1))) {
                    matrix[i][len + i - 1] = 1;
                    count++;
                }
            }
        }
        return count;
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    vector<int> nums = {1, 2, 3, 4};
    ASSERT_EQ(3, numberOfArithmeticSlices(nums)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
