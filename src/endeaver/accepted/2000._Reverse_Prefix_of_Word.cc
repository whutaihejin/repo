#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string reversePrefix(string word, char ch) {
    int h = 0, limit = word.size();
    for (h = 0; h < limit; ++h) {
      if (word[h] == ch) {
        break;
      }
    }
    if (h >= limit) {
      return word;  // do nothing
    }
    for (int l = 0; l < h; ++l, h--) {
      std::swap(word[l], word[h]);
    }
    return word;
  }
};

int main() {
  Solution s;
  string word = "abcdefd";
  string target = s.reversePrefix(word, 'd');
  assert("dcbaefd" == target);
  return 0;
}
