#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

    string removeKdigits(string num, int k) {
        std::vector<char> stack;
        for (size_t i = 0; i < num.size(); ++i) {
            char c = num[i];
            while (k > 0 && !stack.empty() && stack.back() >= c) {
                stack.pop_back();
                k--;
            }
            stack.push_back(c);
        }
        // trim leading zero
        if (stack.front() == '0') {
            size_t l = 0, h = 0;
            for (; h < stack.size(); ++h) {
                if (stack[h] != '0') break;
            }
            for (; h < stack.size(); ++h, ++l) {
                stack[l] = stack[h];
            }
        }
        return num.empty() ? "0" : num;
    }

int main() {
    assert("200" == removeKdigits("10200", 1));
    assert("1219" == removeKdigits("1432219", 3));
    assert("0" == removeKdigits("10", 2));
    return 0;
}
