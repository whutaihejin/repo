#include <iostream>
#include <map>

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
public:
    Solution() {
        // for row 1
        row_hash['q'] = 1; row_hash['Q'] = 1;
        row_hash['w'] = 1; row_hash['W'] = 1;
        row_hash['e'] = 1; row_hash['E'] = 1;
        row_hash['r'] = 1; row_hash['R'] = 1;
        row_hash['t'] = 1; row_hash['T'] = 1;
        row_hash['y'] = 1; row_hash['Y'] = 1;
        row_hash['u'] = 1; row_hash['U'] = 1;
        row_hash['i'] = 1; row_hash['I'] = 1;
        row_hash['o'] = 1; row_hash['O'] = 1;
        row_hash['p'] = 1; row_hash['P'] = 1;
        // for row 2
        row_hash['a'] = 2; row_hash['A'] = 2;
        row_hash['s'] = 2; row_hash['S'] = 2;
        row_hash['d'] = 2; row_hash['D'] = 2;
        row_hash['f'] = 2; row_hash['F'] = 2;
        row_hash['g'] = 2; row_hash['G'] = 2;
        row_hash['h'] = 2; row_hash['H'] = 2;
        row_hash['j'] = 2; row_hash['J'] = 2;
        row_hash['k'] = 2; row_hash['K'] = 2;
        row_hash['l'] = 2; row_hash['L'] = 2;
        // for row 3
        row_hash['z'] = 3; row_hash['Z'] = 3;
        row_hash['x'] = 3; row_hash['X'] = 3;
        row_hash['c'] = 3; row_hash['C'] = 3;
        row_hash['v'] = 3; row_hash['V'] = 3;
        row_hash['b'] = 3; row_hash['B'] = 3;
        row_hash['n'] = 3; row_hash['N'] = 3;
        row_hash['m'] = 3; row_hash['M'] = 3;
    }

    vector<string> findWords(vector<string>& words) {
        std::vector<std::string> results;
        for (size_t i = 0; i < words.size(); ++i) {
            std::string& word = words[i];
            int base = row_hash[word[0]];
            for (size_t j = 1; j < word.size(); ++j) {
                if (row_hash[word[j]] != base) continue;
            }
            results.push_back(word);
        }
        return results;
    }

private:
    std::map<char, int> row_hash;
};
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
