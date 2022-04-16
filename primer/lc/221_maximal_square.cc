#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Time Limit Exceeded
class Solution1 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int area = 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[j] = dp[j] + 1;
                } else {
                    dp[j] = 0;
                }
            }
            // cal square
            for (int l = 1; l <= n; ++l) {
                for (int i = 0; i <= n - l; ++i) {
                    int j = i + l - 1, m = dp[i];
                    for (int k = i; k <= j; ++k) m = min(m, dp[k]);
                    area = max(area, min(m, l) * min(m, l));
                }
            }
        }
        return area;
    }
};

// AC, O(n^2)
class Solution2 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int area = 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[j] = dp[j] + 1;
                } else {
                    dp[j] = 0;
                }
            }
            for (int i = 0; i < n; ++i) {
                int minx = dp[i];
                for (int j = i; j < n; ++j) {
                    minx = min(minx, dp[j]);
                    int v = min(minx, j - i + 1);
                    area = max(area, v * v);
                }
            }
        }
        return area;
    }
};

// AC, O(n)
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        int area = 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[j] = dp[j] + 1;
                } else {
                    dp[j] = 0;
                }
            }
            area = max(area, Square(dp));
        }
        return area;
    }

    int Square(vector<int>& nums) {
        int area = 0;
        vector<int> stack{-1};
        for (int i = 0; i <= nums.size(); ++i) {
            int val = i < nums.size() ? nums[i] : 0;
            while (stack.size() >= 2 && val < nums[stack.back()]) {
                int height = nums[stack.back()]; stack.pop_back();
                int width = i - stack.back() - 1; // This is impoart! Amazing idea!
                int v = min(height, width);
                area = max(area, v * v);
            }
            stack.push_back(i);
        }
        return area;
    }
};

int main() {
    Solution s;
    {
        vector<int> nums{3, 1, 3, 2, 2};
        assert(4 == s.Square(nums));
    }
    {
        vector<int> nums{4, 1, 4, 3};
        assert(4 == s.Square(nums));
    }
    return 0;
}
