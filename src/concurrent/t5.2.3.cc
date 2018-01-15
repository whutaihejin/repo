#include <thread>
#include <iostream>
#include <atomic>

int main() {
    // std::atomic<bool>
    std::atomic<bool> b(true);
    std::cout << b << std::endl;
    b = false;
    std::cout << b << std::endl;

    // the assignment operators they support return values
    // rather than references.
    // (b = false) = true;
    bool x = false;
    (x = false) = true;

    std::atomic<bool> bval(true);
    bool val = bval.exchange(true);
    std::cout << bval << " " << val << std::endl;
    val = bval.exchange(false);
    std::cout << bval << " " << val << std::endl;

    //
    std::atomic<bool> bbval(true);
    bool expect = false;
    while (!bbval.compare_exchange_weak(expect, true) && !expect) {
       std::cout << "compare_exchange_weak fail" << std::endl;
    }
    std::cout << bbval << " " << expect << std::endl;
    return 0;
}
