#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace {
  vector<string> fizzBuzz(int n) {
    vector<string> vec;
    for (int i = 1; i <= n; ++i) {
      if (i % 15 == 0) {
        vec.push_back("FizzBuzz");
      } else if (i % 3 == 0) {
        vec.push_back("Fizz");
      } else if (i % 5 == 0) {
        vec.push_back("Buzz");
      } else {
        vec.push_back(to_string(i));
      }
    }
    return vec;
  }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(2, 2); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
