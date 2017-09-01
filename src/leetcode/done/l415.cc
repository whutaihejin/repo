#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  string addStrings(string num1, string num2) {
    std::string sum(std::max(num1.size(), num2.size()), '0');
    int i1 = (int)num1.size() - 1, i2 = (int)num2.size() - 1;
    int k = sum.size() - 1, carry = 0;
    for (; i1 >= 0 || i2 >= 0; i1--, i2--) {
      int v1 = i1 < 0 ? 0 : num1[i1] - '0';
      int v2 = i2 < 0 ? 0 : num2[i2] - '0';
      int val = v1 + v2 + carry;
      sum[k--] = val % 10 + '0';
      carry = val / 10;
    }
    if (carry) sum.insert(0, 1, carry + '0');
    return sum;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
