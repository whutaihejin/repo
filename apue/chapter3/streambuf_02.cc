#include <stdio.h>
#include <iostream>
#include <sstream>

class UpperCaseStreamBuf : public std::streambuf {
protected:
    virtual int_type overflow(int_type c) {
        if (c != EOF) {
            c = std::toupper(c);
            if (putchar(c) == EOF) {
                return EOF;
            }
        }
        return c;
    }
};

int main() {
    UpperCaseStreamBuf buf;

    std::ostream out(&buf);

    // 31 hexadecimal: 1F
    out << "31 hexadecimal:" << std::hex << 31 << std::endl;
    out << "a=" << 'a' << std::endl;
    return 0;
}
