#include <iostream>

class LogMessageVoidify {
public:
    LogMessageVoidify() {}
    void operator&(std::ostream&) {
        std::cout << "heihei" << std::endl;
    }
};

class Info {
public:
    Info(int v): val(v) {}
private:
    friend std::ostream& operator<<(std::ostream& os, const Info&);
    int val;
};

std::ostream& operator<<(std::ostream& os, const Info& info) {
    std::cout << "heihei" << std::endl;
    os << info.val;
    return os;
}

int main() {
    Info info(12);
    // std::cout << info << std::endl;
    true ? (void)0 : LogMessageVoidify() & std::cout << info << std::endl;
    return 0;
}
