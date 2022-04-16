#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution1 {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size(), ans = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (B[j - 1] == A[i -1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                std::cout << dp[i][j] << ",";
                ans = max(ans, dp[i][j]);
            }
            std::cout << std::endl;
        }
        return ans;
    }
};

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size(), ans = 0;
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            for (int j = n; j >= 1; --j) {
                if (B[j - 1] == A[i -1]) {
                    dp[j] = dp[j - 1] + 1;
                } else {
                    dp[j] = 0;
                }
                std::cout << dp[j] << ",";
                ans = max(ans, dp[j]);
            }
            std::cout << std::endl;
        }
        return ans;
    }
};

int main() {
    vector<int> A{1, 2, 3, 2, 1};
    vector<int> B{3, 2, 1, 4, 7};
    Solution s;
    assert(3 == s.findLength(A, B));
}
