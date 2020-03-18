#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

    string removeKdigits(string num, int k) {
        std::string stack;
        for (size_t i = 0; i < num.size(); ++i) {
            char c = num[i];
            while (k > 0 && !stack.empty() && stack.back() >= c) {
                stack.pop_back();
                k--;
            }
            stack.push_back(c);
        }
        // trim leading zero
        stack.erase(0, stack.find_first_not_of('0'));
        return stack.empty() ? "0" : stack;
    }

int main() {
    std::string v = "  xx x";
    v.erase(0, v.find_first_not_of(' '));
    assert("xx x" == v);

    v = "xx";
    v.erase(0, v.find_first_not_of(' '));
    assert("xx" == v);


    assert("200" == removeKdigits("10200", 1));
    assert("1219" == removeKdigits("1432219", 3));
    assert("0" == removeKdigits("10", 2));
    return 0;
}
