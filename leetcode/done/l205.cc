#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
    bool isIsomorphic(string s, string t) {
        if (s == t) return true;
        char map[256] = {0};
        char rmap[256] = {0};
        for (int i = 0; i < s.size(); ++i) {
            int index = s[i];
            if (!map[index]) {
                if (rmap[t[i]]) return false;
                map[index] = t[i];
                rmap[t[i]] = index;
            } else if (map[index] != t[i]) return false;
        }
        return true;
    }
} // anonymous namespace

TEST(isIsomorphicTest, Case0) {
    ASSERT_TRUE(isIsomorphic("", "")); 
    ASSERT_TRUE(isIsomorphic("a", "a")); 
    ASSERT_TRUE(isIsomorphic("a", "b")); 
    ASSERT_TRUE(isIsomorphic("aa", "bb")); 
    ASSERT_FALSE(isIsomorphic("ab", "aa")); 
    ASSERT_TRUE(isIsomorphic("egg", "add")); 
    ASSERT_TRUE(isIsomorphic("paper", "title")); 
    ASSERT_FALSE(isIsomorphic("foo", "bar")); 
    ASSERT_FALSE(isIsomorphic("aaa", "bbc")); 
    ASSERT_TRUE(isIsomorphic("turtle", "tletur"));
    ASSERT_TRUE(isIsomorphic("13", "42"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
