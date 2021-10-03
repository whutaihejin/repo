#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "base_util.h"

using namespace std;

class Solution {
 public:
  void computePrefixFunction(const string& P, vector<int>& pi) {
    assert(P.size() == pi.size());
    int m = P.size(), k = 0;
    pi[0] = 0;
    for (int q = 1; q < m; ++q) {
      while (k > 0 && P[k] != P[q]) {
        k = pi[k - 1];
      }
      if (P[k] == P[q]) {
        k = k + 1;
      }
      pi[q] = k;
    }
  }

  int KMPMatcher(const string& T, const string& P) {
    if (P.empty()) return 0;
    if (T.empty()) return -1;
    vector<int> pi(P.size(), 0);
    computePrefixFunction(P, pi);
    int n = T.size(), m = P.size();
    for (int i = 0, q = 0; i < n; ++i) {
      while (q > 0 && P[q] != T[i]) {
        q = pi[q - 1];
      }
      if (P[q] == T[i]) {
        q = q + 1;
      }
      if (q == m) {
        return i - m + 1;
      }
    }
    return -1;
  }

  int strStr(string haystack, string needle) {
    return KMPMatcher(haystack, needle);
  }
};

int main() {
  Solution s;
  // string p = "ababaca";
  // string p = "ababbabbabbababbabb";
  // string p = "ababb";
  string p = "issip";
  vector<int> pi(p.size(), 0);
  s.computePrefixFunction(p, pi);
  Print(pi);
  assert(4 == s.KMPMatcher("mississippi", "issip"));

  int pos = s.KMPMatcher("xababacax", "ababaca");
  std::cout << "occurs index: " << pos << std::endl;

  assert(0 == s.KMPMatcher("a", "a"));
  assert(-1 == s.KMPMatcher("a", "b"));
  return 0;
}
