/*
 * @lc app=leetcode id=97 lang=cpp
 *
 * [97] Interleaving String
 *
 * https://leetcode.com/problems/interleaving-string/description/
 *
 * algorithms
 * Hard (28.09%)
 * Likes:    803
 * Dislikes: 38
 * Total Accepted:    113.9K
 * Total Submissions: 403.8K
 * Testcase Example:  '"aabcc"\n"dbbca"\n"aadbbcbcac"'
 *
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and
 * s2.
 * 
 * Example 1:
 * 
 * 
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 * 
 * 
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int row = s1.size(), column = s2.size();
        vector<vector<bool> > f(row + 1, vector<bool>(column + 1, true));
        // init first column and first row
        for (int i = 1; i <= row; ++i) {
            f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
        }
        for (int j = 1; j <= column; ++j) {
            f[0][j] = f[0][j - 1] && s2[j - 1] == s3[j - 1];
        }

        // k means the size of s3, aka s3[0, k - 1]
        // i means the size of s1, aka s1[0, i - 1]
        // j means the size of s2, aka s2[0, j - 1]
        for (int k = 1; k <= s3.size(); ++k) {
            for (int i = 0; i <= k; ++i) {
                int j = k - i;
                if (i == 0) {
                    f[i][j] = f[i][j - 1] && s2[j - 1] == s3[j - 1];
                } else if (j == 0) {
                    f[i][j] = f[i - 1][j] && s1[i - 1] && s3[i -  1];
                } else {
                    if (s3[k - 1] == s1[i - 1]) {
                        if (s3[k - 1] == s2[j - 1]) {
                            f[i][j] = f[i - 1][j] || f[i][j - 1];
                        } else {
                            f[i][j] = f[i - 1][j];
                        }
                    } else {
                        if (s3[k - 1] == s2[j - 1]) {
                            f[i][j] = f[i][j - 1];
                        } else {
                            f[i][j] = false;
                        }
                    }
                }
            }
        }
        // final check
        for (int i = 0; i <= row; ++i) {
            int j = s3.size() - i;
            if (f[i][j]) return true;
        }
        return false;
    }
};

int main() {
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";
    Solution s;
    std::cout << s.isInterleave(s1, s2, s3) << std::endl;
    return 0;
}

