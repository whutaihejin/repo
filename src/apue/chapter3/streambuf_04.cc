#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <streambuf>

class FdOutRealBuf : public std::streambuf {
public:
    FdOutRealBuf() {
        setp(buf_, buf_ + BUFFER_SIZE);
    }

    virtual ~FdOutRealBuf() {
        Sync();
    }

protected:
    // write to stdout
    int FlushBuffer() {
        int num = pptr() - pbase();
        if (write(STDOUT_FILENO, buf_, num) != num) {
            return EOF;
        }
        pbump(-num);
        return num;
    }
    // when the buffer is full, pptr() == epptr(), this function will be called
    virtual int_type overflow(int_type c) {
        int i = 0;
        for (i = 0; i < BUFFER_SIZE; ++i) {
            printf("%d-->%c\n", i, buf_[i]);
        }
        printf("------\n%d-->%c\n", i, c);
        if (c != EOF) {
            *pptr() = c;
            pbump(1);
        }
        if (FlushBuffer() == EOF) {
            return EOF;
        }
        return c;
    }
    // synchronize write
    virtual int Sync() {
        return FlushBuffer() == EOF ? -1 : 0;
    }
protected:
    static const int32_t BUFFER_SIZE = 5;
    char buf_[BUFFER_SIZE];
};

int main() {
    std::streambuf* last_buf = std::cout.rdbuf();
    FdOutRealBuf fd_out_read_buf;
    std::cout.rdbuf(&fd_out_read_buf);
    std::cout << "123456";
    std::cout.rdbuf(last_buf);
    return 0;
}
