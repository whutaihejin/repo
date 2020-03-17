#include <iostream>
#include <bitset>
#include <string>
#include <assert.h>

int main() {
    // case 1
    std::bitset<8> b1;
    assert("00000000" == b1.to_string());
    // case 2
    std::bitset<13> b2(0xbeef);
    assert("1111011101111" == b2.to_string());
    // case 3
    std::bitset<20> b3(0xbeef);
    assert("00001011111011101111" == b3.to_string());
    // case 4
    std::bitset<128> b4(~0ULL);
    std::string str1(64, '0');
    std::string str2(64, '1');
    std::string str = str1 + str2;
    assert(str == b4.to_string());
    // case 5
    return 0;
}
