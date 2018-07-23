#include <iostream>

int main() {
    union un {
        short val;
        char ch[sizeof(short)];
    };
    un x;
    x.val = 0x0102;
    if (sizeof(short) == 2U) {
        if (x.ch[0] == 0x02 && x.ch[1] == 0x01) {
            std::cout << "little endian" << std::endl;
        } else if (x.ch[0] == 0x01 && x.ch[1] == 0x02) {
            std::cout << "big-endian" << std::endl;
        } else {
            std::cout << "unknown" << std::endl;
        }
    } else {
        std::cout << "sizeof(short)=" << sizeof(short) << std::endl;
    }
    return 0;
}
