#include <iostream>
#include <atomic>

class SpinLockMutex {
public:
    SpinLockMutex(): flag_(ATOMIC_FLAG_INIT) {}

    void Lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {
            // ignore
        }
    }

    void Unlock() {
        flag_.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag_;
};

int main() {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    flag.clear(std::memory_order_release);
    bool x = flag.test_and_set();
    std::cout << x << std::endl;

    // can't copy construction
    // std::atomic_flag copy(flag);
    // can't assignment
    // std::atomic_flag assign = flag;
    return 0;
}
