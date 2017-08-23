#include <iostream>
#include <math.h>
#include "gtest/gtest.h"

using namespace std;

namespace {
    bool isPrime(int n) {
        if (n <= 3) return n > 1;
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) return false;
        }
        return false;
    }

    int countPrimes(int n) {
        int count = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime(i)) count++;
        }
        return count; 
    }
} // anonymous namespace

TEST(YourTest, Case0) {
    ASSERT_EQ(0, countPrimes(-1)); 
    ASSERT_EQ(0, countPrimes(-20)); 
    ASSERT_EQ(0, countPrimes(0)); 
    ASSERT_EQ(0, countPrimes(1)); 
    ASSERT_EQ(0, countPrimes(2)); 
    ASSERT_EQ(1, countPrimes(3)); 
    ASSERT_EQ(2, countPrimes(4)); 
    ASSERT_EQ(2, countPrimes(5)); 
    ASSERT_EQ(3, countPrimes(6)); 
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
