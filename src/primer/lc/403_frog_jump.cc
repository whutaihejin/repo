#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Memory Limit Exceeded
class Solution {
public:
    bool canCross(vector<int>& stones) {
        int m = stones.size(), n = m * (m - 1) / 2;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][1] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                for (int k = i - 1; k >= 0; k--) {
                    int s = max(0, j - 1), e = min(n - 1, j + 1);
                    for (int l = s; l <= e; ++l) {
                        if (dp[k][l] && stones[k] + l == stones[i]) {
                            dp[i][j] = 1; break;
                        }
                    }
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            if (dp[m - 1][j]) return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    {
        vector<int> stones{0,1,3};
        assert(s.canCross(stones));
    }
    {
        vector<int> stones{0,1,3,5,6,8,12,17};
        assert(s.canCross(stones));
    }
    {
        vector<int> stones{0,1,2,3,4,8,9,11};
        assert(!s.canCross(stones));
    }
    return 0;
}
