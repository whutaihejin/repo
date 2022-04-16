#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        dp[0][0] = 1;
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j - 2] || dp[i - 1][j - 2] || dp[i - 1][j];
                    } else {
                        dp[i][j] = dp[i][j - 2];
                    }
                } else if (p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] && dp[i - 1][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution s;
    assert(!s.isMatch("aa", "a"));
    assert(s.isMatch("aa", "a*"));
    assert(s.isMatch("ab", ".*"));
    assert(s.isMatch("aab", "c*a*b"));
    assert(!s.isMatch("mississippi", "mis*is*p*."));
    return 0;
}
