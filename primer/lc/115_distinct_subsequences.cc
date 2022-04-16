#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long>> dp(m + 1, vector<long>(n + 1, 0));
        // If target is empty, there is one subsequence that delete all source string.
        for (int i = 0; i <= m; ++i) dp[i][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution s;
    assert(2 == s.numDistinct("bab", "b"));
    assert(2 == s.numDistinct("rabb", "rab"));
    assert(3 == s.numDistinct("rabbbit", "rabbit"));
    assert(5 == s.numDistinct("babgbag", "bag"));
    return 0;
}
