#include <iostream>
#include <math.h>
#include "gtest/gtest.h"

using namespace std;

namespace {
    int countPrimes(int n) {
        int count = 0;
        if (n <= 1) return count;
        int* arr = new int[n];
        for (int i = 2; i < n; ++i) {
            arr[i] = true;
        }
        for (int i = 2; i * i <  n; ++i) {
            if (!arr[i]) continue;
            for (int j = i * i; j < n; j += i) {
                arr[j] = false;
            }
        }
        for (int i = 2; i <  n; ++i) {
            if (arr[i]) count++;
        }
        delete[] arr;
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
