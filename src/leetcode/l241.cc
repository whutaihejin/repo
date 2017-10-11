#include <iostream>
#include <stdlib.h>
#include <vector>
#include <gtest/gtest.h>

#include "lib/util.h"
using namespace std;

namespace {
    struct Token {
        enum Type {OPERAND, OPERATOX};
        Token(Type type, int operand = 0): type_(type), operand_(operand) {
        }
        Type type_;
        union {
            char operatox_;
            int operand_;
        };
    };

    void Tokenize(std::string& input, std::vector<Token>& tokens) {
        for (size_t low = 0, high = 0; low < input.size();) {
            char ch = input[low];
            if (ch == '+' || ch == '-' || ch == '*') {
                tokens.push_back(Token(Token::OPERATOX, ch));
                low++;
                continue;
            }
            int val = 0;
            for (high = low; high < input.size() && isdigit(input[high]); high++) {
                val = val * 10 + input[high] - '0';
            }
            tokens.push_back(Token(Token::OPERAND, val));
            low = high;
        }
    }

    vector<int> cal(std::vector<Token>& tokens, int low, int high) {
        std::vector<int> results;
        if (low == high) {
            results.push_back(tokens[low].operand_);
            return results;
        }
        for (int i = low; i <= high; i++) {
            if (tokens[i].type_ == Token::OPERATOX) {
                std::vector<int> left = cal(tokens, low, i - 1);
                std::vector<int> right = cal(tokens, i + 1, high);
                for (size_t l = 0; l < left.size(); ++l) {
                    for (size_t r = 0; r < right.size(); ++r) {
                        switch (tokens[i].operatox_) {
                            case '+': results.push_back(left[l] + right[r]); break;
                            case '-': results.push_back(left[l] - right[r]); break;
                            case '*': results.push_back(left[l] * right[r]); break;
                        }
                    }
                }
            }
        }
        return results;
    }

    vector<int> diffWaysToCompute(string input) {
        std::vector<Token> tokens;
        Tokenize(input, tokens);
        return cal(tokens, 0, tokens.size() - 1);
    }
} // anonymous namespace

TEST(diffWaysToComputeTest, Case0) {
    std::vector<int> r = diffWaysToCompute("123");
    ASSERT_EQ("123", leetcode::toString(r));
    r = diffWaysToCompute("5*2+3");
    ASSERT_EQ("25,13", leetcode::toString(r));
    r = diffWaysToCompute("2*3+4*5");
    ASSERT_EQ("-34,-14,-10,-10,10", leetcode::toString(r));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
