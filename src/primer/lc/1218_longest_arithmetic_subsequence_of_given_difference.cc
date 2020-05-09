#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

// Time Limit Exceeded
class Solution2 {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        vector<int> dp(arr.size(), 1);
        int ans = 0;
        for (int i = 1; i < arr.size(); ++i) {
            int span = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] == arr[i] - difference) {
                    span = max(span, dp[j]);
                }
            }
            dp[i] = span + 1;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = 0;
        vector<int> dp(arr.size(), 1);
        unordered_map<int, int> kv{{arr[0], 1}};
        for (int i = 1; i < arr.size(); ++i) {
            // cal
            if (auto it = kv.find(arr[i] - difference); it != kv.end()) {
                dp[i] += it->second;
            }
            // put
            if (auto it = kv.find(arr[i]); it != kv.end()) {
                it->second = max(it->second, dp[i]);
            } else {
                kv[arr[i]] = dp[i];
            }
            // max answer
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

int main() {
    Solution s;
    {
        vector<int> nums{1, 2, 3, 4};
        assert(4 == s.longestSubsequence(nums, 1));
    }
    {
        vector<int> nums{1,3,5,7};
        assert(1 == s.longestSubsequence(nums, 1));
    }
    {
        vector<int> nums{1,5,7,8,5,3,4,2,1};
        assert(4 == s.longestSubsequence(nums, -2));
    }
    return 0;
}
