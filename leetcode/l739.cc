#include <iostream>
#include <stack>
#include <gtest/gtest.h>

using namespace std;

namespace {
	vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::vector<int> result(temperatures.size());
        std::stack<int> stack;
        for (int i = 0; i < temperatures.size(); ++i) {
            while (stack.empty()) {
                int top = stack.top();
                int val = top >> 24, index = (0x00FFFFFF & top);
                if (val >= temperatures[i]) {
                    break;
                }
                result[index] = i - index;
            }
            int val = (temperatures[i] << 24) | i;
            stack.push(val);
        }
        return result;
    } 
} // anonymous namespace

TEST(YourTest, Case0) {
    std::vector<int> vec(10, 71);
    vec.push_back(72);
    const std::vector<int>& v = dailyTemperatures(vec);
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
