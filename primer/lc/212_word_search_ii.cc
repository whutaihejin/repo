#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<string, int> kv;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        kv.clear();
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[0].size(); ++j) {
                for (auto word: words) {
                    if (kv.find(word) == kv.end()) {
                        dfs(board, word, i, j, 0);
                    }
                }
            }
        }
        std::vector<string> ans;
        for (auto it = kv.begin(); it != kv.end(); ++it) ans.push_back(it->first);
        return ans;
    }

    bool dfs(vector<vector<char>>& board, string& s, int i, int j, int k) {
        if (k >= s.size()) {
            kv[s] = 1;
            return true;
        }
        if (i >= 0 && i < board.size() && j >= 0 && j < board[0].size()) {
            if (board[i][j] == s[k]) { // match current letter then find the next one
                char back = board[i][j];
                board[i][j] = ' ';
                if (dfs(board, s, i + 1, j, k + 1)) {
                    board[i][j] = back; return true;
                }
                if (dfs(board, s, i - 1, j, k + 1)) {
                    board[i][j] = back; return true;
                }
                if (dfs(board, s, i, j - 1, k + 1)) {
                    board[i][j] = back; return true;
                }
                if (dfs(board, s, i, j + 1, k + 1)) {
                    board[i][j] = back; return true;
                }
                board[i][j] = back;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    {
        vector<vector<char>> board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };
        vector<string> words = {"oath","pea","eat","rain"};
        vector<string> ans = s.findWords(board, words);
        assert(2 == ans.size());
        for (auto w: ans) {
            std::cout << w << std::endl;
        }
    }
    {
        vector<vector<char>> board = {
            {'a','b'},
            {'c','d'}
        };
        vector<string> words = {"ab","cb","ad","bd","ac","ca","da","bc","db","adcb","dabc","abb","acb"};
        vector<string> ans = s.findWords(board, words);
        for (auto w : ans) {
            std::cout << w << std::endl;
        }
        assert(5 == ans.size());
    }
    return 0;
}
