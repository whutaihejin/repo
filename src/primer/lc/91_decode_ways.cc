#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = s[0] - '0' > 0 ? 1 : 0;
        for (size_t i = 2; i <= n; ++i) {
            if (s[i - 1] != '0') {
                dp[i] = dp[i - 1];
            }
            if (s[i - 2] != '0') {
                int v = (s[i - 2] - '0') * 10 + s[i -1] - '0';
                if (v >= 1 && v <= 26) {
                    dp[i] += dp[i - 2];
                }
            }
        }
        return dp[n];
    }
};

int main() {
    Solution s;
    assert(0 == s.numDecodings(""));
    assert(1 == s.numDecodings("10"));
    assert(0 == s.numDecodings("0"));
    assert(1 == s.numDecodings("1"));
    assert(2 == s.numDecodings("12"));
    assert(0 == s.numDecodings("01"));
    assert(1 == s.numDecodings("36"));
    return 0;
}
