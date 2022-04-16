#include <iostream>
#include <unordered_map>
#include <lib/util.h>

#include <gtest/gtest.h>

using namespace std;

namespace {
  vector<string> split(const std::string& str) {
    std::vector<string> vec;
    int l = 0;
    for (size_t h = 0; h < str.size(); ++h) {
      if (str[h] == ' ') {
        vec.push_back(str.substr(l, h - l));
        l = h + 1;
        continue;
      }
    }
    vec.push_back(str.substr(l, str.size() - l));
    return vec;
  }

  bool wordPattern(string pattern, string str) {
    vector<std::string> words = split(str);
    if (pattern.size() != words.size()) return false;
    std::unordered_map<char, string> map;
    std::unordered_map<string, char> rmap;
    for (size_t i = 0; i < pattern.size(); ++i) {
      if (map.count(pattern[i]) > 0) {
        if (map[pattern[i]] != words[i]) return false;
      }
      if (rmap.count(words[i]) > 0) {
        if (rmap[words[i]] != pattern[i]) return false;
      }
      map[pattern[i]] = words[i];
      rmap[words[i]] = pattern[i];
    }
    return true;            
  }
} // anonymous namespace

TEST(YourTest, Case0) {
  // ASSERT_EQ("say,bad,oo", leetcode::toString(split("say bad oo")));
  ASSERT_TRUE(wordPattern("aaa", "dog dog dog"));
  ASSERT_FALSE(wordPattern("aab", "dog dog dog"));
  ASSERT_TRUE(wordPattern("abba", "dog cat cat dog"));
  ASSERT_FALSE(wordPattern("abba", "dog cat cat fish"));
  ASSERT_FALSE(wordPattern("aaaa", "dog cat cat dog"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
