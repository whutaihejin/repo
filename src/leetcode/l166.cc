#include <iostream>
#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h> // for abs
#include <unordered_map>

using namespace std;

namespace {
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        std::string ret;
        int64_t x = numerator, y = denominator;
        // determine the sign
        if ((x > 0) ^ (y > 0)) ret.push_back('-');
        x = abs(x), y = abs(y);
        ret += std::to_string(x / y);
        // in case no fractional part
        if (x % y == 0) return ret;

        ret.push_back('.');
        std::unordered_map<int, int> map;
        for (int64_t r = x % y; r; r %= y) {
            if (map.count(r) == 1) {
                ret.insert(map[r], 1, '(');
                ret.push_back(')');
                break;
            }
            map[r] = ret.size();
            r *= 10;
            ret.push_back(r / y + '0');
        }
        return ret;
        
    }
} // anonymous namespace

TEST(fractionToDecimalTest, Case0) {
    ASSERT_EQ("0", fractionToDecimal(0, -3)); 
    ASSERT_EQ("0", fractionToDecimal(0, -1));
    ASSERT_EQ("0", fractionToDecimal(0, 1));
    ASSERT_EQ("0", fractionToDecimal(0, 3));
    ASSERT_EQ("-0.(3)", fractionToDecimal(-1, 3));
    ASSERT_EQ("0.(3)", fractionToDecimal(-1, -3));
    ASSERT_EQ("-0.(3)", fractionToDecimal(1, -3));
    ASSERT_EQ("0.(3)", fractionToDecimal(1, 3));
    ASSERT_EQ("-2147483648", fractionToDecimal(-2147483648, 1));
    ASSERT_EQ("2147483648", fractionToDecimal(-2147483648, -1));
    ASSERT_EQ("0.(01)", fractionToDecimal(1, 99));
    ASSERT_EQ("0.01", fractionToDecimal(1, 100));
    /*ASSERT_EQ("(01)", fraction(1, 99)); 
    ASSERT_EQ("(3)", fraction(1, 3)); 
    ASSERT_EQ("(6)", fraction(2, 3)); 
    ASSERT_EQ("5", fraction(1, 2)); 
    ASSERT_EQ("(142857)", fraction(1, 7)); 
    ASSERT_EQ("01", fraction(1, 100)); 
    ASSERT_EQ("", fraction(0, 100)); 
    ASSERT_EQ("2", fractionToDecimal(2, 1)); 
    ASSERT_EQ("0.5", fractionToDecimal(1, 2)); 
    ASSERT_EQ("0.(6)", fractionToDecimal(2, 3)); 
    ASSERT_EQ("0", fractionToDecimal(0, 2));
    ASSERT_EQ("2147483648", fractionToDecimal(-2147483648, -1));
    ASSERT_EQ("-2147483648", fractionToDecimal(-2147483648, 1));*/
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
