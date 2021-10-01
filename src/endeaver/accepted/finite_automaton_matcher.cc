#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int finiteAutomatonMatcher(const string& t, const string& p,
                             vector<vector<int>>& f) {
    int n = t.size(), m = p.size();
    int q = 0;
    for (int i = 0; i < n; ++i) {
      q = f[q][t[i]];
      if (q == m) {
        return i + 1 - m;
      }
    }
    return -1;
  }

  // This procedure computes 'transition' in a straightforward manner according
  // to its definition.
  void computeTransitionFunction(const string& p, vector<vector<int>>& f) {
    int m = p.size();
    f = vector<vector<int>>(m + 1, vector<int>(256, 0));
    for (int q = 0; q <= m; ++q) {
      for (int c = 'a'; c <= 'z'; ++c) {
        string t = p.substr(0, q);
        t += c;
        int k = min(q + 1, m);
        for (; k > 0; k--) {
          int offset = q + 1 - k, matched = 1;
          for (int i = 0; i < k; ++i) {
            if (p[i] != t[i + offset]) {
              matched = 0;
              break;
            }
          }
          if (matched) {
            break;
          }
        }
        f[q][c] = k;
      }
    }
  }
};

int main() {
  Solution s;
  string p = "ababaca";
  vector<vector<int>> f;
  s.computeTransitionFunction(p, f);
  for (size_t i = 0; i <= p.size(); ++i) {
    std::cout << i << "-> " << f[i]['a'] << " " << f[i]['b'] << " " << f[i]['c']
              << std::endl;
  }
  int pos = s.finiteAutomatonMatcher("abababacaba", p, f);
  std::cout << "pattern occurs with shift " << pos << std::endl;
  return 0;
}
