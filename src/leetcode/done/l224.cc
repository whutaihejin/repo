#include <stack>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    int calculate(string s) {
        stack<int> operand;
        stack<char> operatox;
        for (size_t l = 0; l < s.size(); ++l) {
            char ch = s[l];
            switch(ch) {
                case ' ':
                    break;
                case '+':
                case '-':
                    if (!operatox.empty() && operatox.top() != '(') {
                        int right = operand.top(); operand.pop();
                        int left = operand.top(); operand.pop();
                        char op = operatox.top(); operatox.pop();
                        switch (op) {
                            case '+':
                                operand.push(left + right);
                                break;
                            case '-':
                                operand.push(left - right);
                                break;
                            default:
                                exit(1);
                        }
                    }
                    operatox.push(ch);
                    break;
                case '(':
                    operatox.push(ch);
                    break;
                case ')':
                    while (!operatox.empty() && operatox.top() != '(') {
                        int right = operand.top();
                        operand.pop();
                        int left = operand.top();
                        operand.pop();
                        char op = operatox.top();
                        operatox.pop();
                        switch (op) {
                            case '+':
                                operand.push(left + right);
                                break;
                            case '-':
                                operand.push(left - right);
                                break;
                            default:
                                exit(1);
                        }
                    }
                    operatox.pop();
                    break;
                default:
                    size_t h = l;
                    int val = 0;
                    for (; h < s.size() && isdigit(s[h]); ++h) {
                        val = val * 10 + s[h] - '0';
                    }
                    l = h - 1;
                    operand.push(val);
                    break;
            }
        }
        while (!operatox.empty()) {
            int right = operand.top(); operand.pop();
            int left = operand.top(); operand.pop();
            char op = operatox.top(); operatox.pop();
            switch (op) {
                case '+':
                    operand.push(left + right);
                    break;
                case '-':
                    operand.push(left - right);
                    break;
                default:
                    exit(1);
            }
        }
        return operand.top();
    }
} // anonymous namespace

TEST(calculateTest, Case0) {
    ASSERT_EQ(3, calculate("1 + 2")); 
    std::string exp = "1 + 2 - 5 - 3";
    ASSERT_EQ(-5, calculate(exp)); 
    ASSERT_EQ(-5, calculate("1 + ( 2 - 5 ) - 3")); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
