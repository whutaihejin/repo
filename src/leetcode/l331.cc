#include <iostream>
#include <stack>
#include <gtest/gtest.h>

using namespace std;

namespace {
    bool isValidSerialization(string preorder) {
        static const std::string sentinel = "#";
        std::stack<string> stack;
        for (size_t l = 0; l < preorder.size();) {
            size_t h = l;
            while (h < preorder.size() && preorder[h] != ',') h++;
            std::string val = preorder.substr(l, h - l);
            l = h + 1;
            if (val != sentinel) {
                stack.push(val);
            } else {
                if (stack.empty() || stack.top() != sentinel) {
                    stack.push(val);
                    continue;
                }
                while (!stack.empty() && stack.top() == sentinel) {
                    stack.pop();
                    if (stack.empty()) return false;
                    stack.pop();
                }
                stack.push(sentinel);
            }
        }
        return stack.size() == 1U && stack.top() == sentinel;
    }
} // anonymous namespace

TEST(isValidSerializationTest, Case0) {
    ASSERT_TRUE(isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
