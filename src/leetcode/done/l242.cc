#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  bool isAnagram(string s, string t) {
    const int SIZE = 256;
    if (s.size() != t.size()) return false;
    if (s.empty()) return true;
    unsigned char map[SIZE] = {0};
    unsigned char rmap[SIZE] = {0};
    for (int i = 0; i < s.size(); ++i) {
      map[(unsigned char)s[i]]++;
      rmap[(unsigned char)t[i]]++;
    }
    for (int i = 0; i < SIZE; ++i) {
      if (map[i] != rmap[i]) return false;
    }
    return true;
  }
} // anonymous namespace

TEST(isAnagramTest, Case0) {
    ASSERT_TRUE(isAnagram("", "")); 
    ASSERT_TRUE(isAnagram("a", "a")); 
    ASSERT_TRUE(isAnagram("bb", "bb")); 
    ASSERT_TRUE(isAnagram("abba", "aabb")); 
    ASSERT_FALSE(isAnagram("abbaa", "aabb")); 
    ASSERT_TRUE(isAnagram("汉字", "汉字")); 
    ASSERT_TRUE(isAnagram("字汉", "汉字")); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
