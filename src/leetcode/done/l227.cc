#include <stack>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace {
    void doCal(stack<int>& operand, stack<char>& operatox) {
        int right = operand.top(); operand.pop();
        int left = operand.top(); operand.pop();
        int op = operatox.top(); operatox.pop();
        switch (op) {
            case '+':
                operand.push(left + right);
                break;
            case '-':
                operand.push(left - right);
                break;
            case '*':
                operand.push(left * right);
                break;
            case '/':
                operand.push(left / right);
                break;
        }
    }
    
    bool hightPriority(char left, char right) {
        if (left == '*' || left == '/') return true;
        return (right == '+' || right == '-');
    }

    int calculate(string s) {
       stack<int> operand;
       stack<char> operatox;
       for (size_t l = 0, h = 0; l < s.size(); ++l) {
           char ch = s[l];
           if (ch == ' ') continue;
           if (isdigit(ch)) {
               int val = 0;
               h = l;
               while (h < s.size() && isdigit(s[h])) {
                   val = val * 10 + s[h] - '0';
                   h++;
               }
               l = h - 1;
               operand.push(val);
               continue;
           }
           while (!operatox.empty() && hightPriority(operatox.top(), ch)) {
               doCal(operand, operatox);
           }
           operatox.push(ch);
       }
       if (!operatox.empty()) {
           doCal(operand, operatox);
       }
       return operand.top();
    }
} // anonymous namespace

TEST(calculateTest, Case0) {
    ASSERT_EQ(1, calculate("1")); 
    ASSERT_EQ(-5, calculate("1 + 2 - 5 -3")); 
    ASSERT_EQ(8, calculate("1 + 2 * 5 -3")); 
    ASSERT_EQ(-2, calculate("1 + 2 / 5 -3")); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
