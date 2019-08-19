/*
 * @lc app=leetcode id=44 lang=cpp
 *
 * [44] Wildcard Matching
 *
 * https://leetcode.com/problems/wildcard-matching/description/
 *
 * algorithms
 * Hard (22.87%)
 * Likes:    1098
 * Dislikes: 76
 * Total Accepted:    181.3K
 * Total Submissions: 789.1K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*'.
 * 
 * 
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 * 
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * Note:
 * 
 * 
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters
 * like ? or *.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * s = "aa"
 * p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input:
 * s = "cb"
 * p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not
 * match 'b'.
 * 
 * 
 * Example 4:
 * 
 * 
 * Input:
 * s = "adceb"
 * p = "*a*b"
 * Output: true
 * Explanation: The first '*' matches the empty sequence, while the second '*'
 * matches the substring "dce".
 * 
 * 
 * Example 5:
 * 
 * 
 * Input:
 * s = "acdcb"
 * p = "a*c?b"
 * Output: false
 * 
 * 
 */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = p.size(), n = s.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, true));
        for (int j = 0; j <= n; ++j) f[0][j] = j == 0;
        for (int i = 1; i <= m; ++i) f[i][0] = p[i - 1] == '*' ? f[i - 1][0] : false;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                switch (p[i - 1]) {
                    case '*':
                        f[i][j] = f[i - 1][j - 1] || f[i - 1][j] || f[i][j - 1];
                        break;
                    case '?':
                        f[i][j] = f[i - 1][j - 1];
                        break;
                    default:
                        f[i][j] = s[j - 1] == p[i - 1] ? f[i - 1][j - 1] : false;
                        break;
                }
            }
        }
        return f[m][n];
    }
};

