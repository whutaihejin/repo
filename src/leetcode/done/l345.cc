#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  bool isVowel(char ch) {
    switch (ch) {
      case 'a': case 'A':
      case 'e': case 'E':
      case 'i': case 'I':
      case 'o': case 'O':
      case 'u': case 'U':return true;
    }
    return false;
  }
  string reverseVowels(string s) {
    char ch;    
    for (int l = 0, h = s.size() - 1; l < h;) {
      if (!isVowel(s[l])) {l++; continue;}
      if (!isVowel(s[h])) {h--; continue;}
      ch = s[l];
      s[l] = s[h];
      s[h] = ch;
      l++, h--;
    }
    return s;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
