#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<int> f(n + 1, 0); f[0] = 1;
        vector<vector<int>> memo(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int k = i; k >= 0; --k) {
                string sub = s.substr(k, i - k + 1);
                auto it = std::find(wordDict.begin(), wordDict.end(), sub);
                if (it != wordDict.end() && f[k]) {
                    f[i + 1] = 1;
                    memo[i][k] = 1;
                }
            }
        }
        vector<string> ans;
        if (f[n]) {
            string path;
            dfs(s, memo, path, n - 1, n - 1, ans);
        }
        return ans;
    }

    void dfs(const string s, vector<vector<int>>& memo, string& path, int i, int j, vector<string>& ans) {
        if (i < 0 || j < 0) {
            ans.push_back(path);
        } else {
            bool done = false;
            for (int c = j; c >= 0; c--) {
                if (memo[i][c]) {
                    done = true;
                    string origin = path, sub = s.substr(c, j - c + 1);
                    if (path.empty()) path = sub;
                    else path = sub + " " + path;
                    dfs(s, memo, path, c - 1, c - 1, ans);
                    path = origin;
                }
            }
            if (!done) {
                dfs(s, memo, path, i - 1, j, ans);
            }
        }
    }
};

void case1() {
    string s = "abcd";
    vector<string> wordDict{"a","abc","b","cd"};
    Solution solution;
    vector<string> r = solution.wordBreak(s, wordDict);
    assert(r.size() == 1U);
    assert(r[0] == "a b cd");
}

void case2() {
    string s = "catsanddog";
    vector<string> wordDict{"cat","cats","and","sand","dog"};
    // Output: ["cats and dog","cat sand dog"]

    Solution solution;
    vector<string> r = solution.wordBreak(s, wordDict);
    assert(r.size() == 2U);
    assert(r[0] == "cats and dog");
    assert(r[1] == "cat sand dog");
}

int main() {
    case1();
    case2();
    return 0;
}