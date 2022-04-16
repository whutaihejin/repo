#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  // 朴素匹配算法，暴力匹配算法
  // 注意：外层循环的终止条件是 i <= m - n;
  // int strStr(string haystack, string needle) {
  //   int m = haystack.size(), n = needle.size();
  //   for (int i = 0; i <= m - n; ++i) {
  //     int j = 0;
  //     for (; j < n; ++j) {
  //       if (haystack[i + j] != needle[j]) {
  //         break;
  //       }
  //     }
  //     if (j == n) {
  //       return i;
  //     }
  //   }
  //   return -1;
  // }

  // 朴素版KMP算法
  // int strStr(string haystack, string needle) {
  //   if (needle.empty()) {
  //     return 0;
  //   }
  //   // build dfa
  //   const int kR = 256;
  //   int m = haystack.size(), n = needle.size();
  //   vector<vector<int>> dfa(kR, vector<int>(n, 0));
  //   dfa[needle[0]][0] = 1;
  //   for (int x = 0, j = 1; j < n; ++j) {
  //     for (int c = 0; c < kR; ++c) {
  //       dfa[c][j] = dfa[c][x];
  //     }
  //     dfa[needle[j]][j] = j + 1;
  //     x = dfa[needle[j]][x];
  //   }
  //   // pattern search
  //   int i = 0, j = 0;
  //   for (; i < m && j < n; ++i) {
  //     j = dfa[haystack[i]][j];
  //   }
  //   return j >= n ? i - n : -1;
  // }

  // 优化DFA空间大小的KMP算法
  int strStr(string haystack, string needle) {
    if (needle.empty()) {
      return 0;
    }
    // build dfa
    const int kR = 26;
    int m = haystack.size(), n = needle.size();
    vector<vector<int>> dfa(kR, vector<int>(n, 0));
    dfa[needle[0] - 'a'][0] = 1;
    for (int x = 0, j = 1; j < n; ++j) {
      for (int c = 0; c < kR; ++c) {
        dfa[c][j] = dfa[c][x];
      }
      dfa[needle[j] - 'a'][j] = j + 1;
      x = dfa[needle[j] - 'a'][x];
    }
    // pattern search
    int i = 0, j = 0;
    for (; i < m && j < n; ++i) {
      j = dfa[haystack[i] - 'a'][j];
    }
    return j >= n ? i - n : -1;
  }
};

int main() {
  Solution s;
  assert(2 == s.strStr("hello", "ll"));
  assert(-1 == s.strStr("aaaaa", "bba"));
  assert(0 == s.strStr("", ""));
  assert(0 == s.strStr("dfas", ""));
  assert(0 == s.strStr("a", "a"));
  return 0;
}
