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

    //
    std::atomic<bool> atomic_v1(true);
    std::atomic<bool> atomic_v2(false);
    // copying variable of type 'std::atomic<bool>' invokes deleted constructor 
    // std::atomic<bool> atomic_v3 = true;
    // std::atomic<bool> atomic_v4 = false;
    atomic_v2 = true;
    std::cout << "atomic_v2=" << (atomic_v2 = true) << std::endl;
    atomic_v1 = false;
    std::cout << "atomic_v1=" << (atomic_v1 = false) << std::endl;
    
    std::cout << "exchange=" << atomic_v1.exchange(true, std::memory_order_acquire) << std::endl;
    std::cout << "load=" << atomic_v1.load(std::memory_order_acquire) << std::endl;
    std::cout << "exchange=" << atomic_v1.exchange(true, std::memory_order_acquire) << std::endl;
    std::cout << "load=" << atomic_v1.load(std::memory_order_acquire) << std::endl;
    std::cout << "exchange=" << atomic_v1.exchange(false, std::memory_order_acquire) << std::endl;

    return 0;
}
