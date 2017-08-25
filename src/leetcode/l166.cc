#include <iostream>
#include "gtest/gtest.h"

#include <vector>
#include <unordered_set>

using namespace std;

namespace {
    string fraction(int x, int y) {
        std::vector<int> vec;
        std::unordered_set<int> unset;
        std::unordered_set<int>::iterator it;
        x *= 10;
        int div = 0;
        while (x != 0) {
            while (x < y) {
                x *= 10;
                vec.push_back(0);
            }
            div = x / y;
            if ((it = unset.find(div)) != unset.end()) break;
            unset.insert(div);
            vec.push_back(div);
            x = x % y;
        }
        int size = x == 0 ? vec.size() : vec.size() + 2;
        std::string ret(size, '0');
        for (size_t i = 0, j = 0; i < vec.size(); ++i) {
            if (x != 0 && vec[i] == div) ret[j++] = '(';
            ret[j] += vec[i];
        }
        if (x != 0) ret[ret.size() - 1] = ')';
        return ret;
    }
    string fractionToDecimal(int numerator, int denominator) {
        return "";
    }
} // anonymous namespace

TEST(fractionToDecimalTest, Case0) {
    ASSERT_EQ("(3)", fraction(1, 3)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
