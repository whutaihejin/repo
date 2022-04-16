#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

class FdOutBuf : public std::streambuf {
public:
    FdOutBuf(int fd): fd_(fd) {}

protected:
    virtual int_type overflow(int_type c) {
        std::cout << std::endl << "FdOutBuf::overflow" << std::endl;
        if (c != EOF) {
            char z = c;
            if (write(fd_, &z, 1) != 1) {
                return EOF;
            }
        }
        return c;
    }

    virtual std::streamsize xsputn(const char* s, std::streamsize num) {
        std::cout << std::endl << "FdOutBuf::xsputn" << std::endl;
        return write(fd_, s, num);
    }

protected:
    int fd_;
};

class FdOstream : public std::ostream {
public:
    FdOstream(int fd): std::ostream(&buf_), buf_(fd) {}

protected:
    FdOutBuf buf_;
};

int main() {
    FdOstream out(1);
    out << "31 hexadecimal:" << std::hex << 31 << std::endl;
    return 0;
}
