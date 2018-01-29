#include <iostream>
#include <atomic>

class SpinLockMutex {
public:
    // SpinLockMutex(): flag_{ATOMIC_FLAG_INIT} {}
    SpinLockMutex() {}

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

//
static std::atomic_flag static_atomic_flag = ATOMIC_FLAG_INIT;
int main() {
    static std::atomic_flag inner_static_atomic_flag = ATOMIC_FLAG_INIT;
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    flag.clear(std::memory_order_release);
    bool x = flag.test_and_set();
    std::cout << x << std::endl;

    // can't copy construction
    // std::atomic_flag copy(flag);
    // can't assignment
    // std::atomic_flag assign = flag;
    std::atomic_flag fx = ATOMIC_FLAG_INIT;
    std::cout << "test_and_set()=" << fx.test_and_set() << std::endl;
    std::cout << "test_and_set()=" << fx.test_and_set() << std::endl;
    fx.clear(std::memory_order_release);
    std::cout << "test_and_set()=" << fx.test_and_set() << std::endl;
    return 0;
}
