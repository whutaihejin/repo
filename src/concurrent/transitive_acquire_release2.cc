#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<int> data[5];
std::atomic<int> sync(0);

void thread1() {
    data[0].store(42, std::memory_order_relaxed);
    data[1].store(97, std::memory_order_relaxed);
    data[2].store(17, std::memory_order_relaxed);
    data[3].store(-141, std::memory_order_relaxed);
    data[4].store(2019, std::memory_order_relaxed);
    sync.store(1, std::memory_order_release);
}

void thread2() {
    int expect = 1;
    while (!sync.compare_exchange_strong(expect, 2, std::memory_order_acq_rel)) {
        expect = 1;
    }
}

void thread3() {
    while (sync.load(std::memory_order_acquire) < 2) {
        // ignore
    }
    assert(42 == data[0].load(std::memory_order_relaxed));
    assert(97 == data[1].load(std::memory_order_relaxed));
    assert(17 == data[2].load(std::memory_order_relaxed));
    assert(-141 == data[3].load(std::memory_order_relaxed));
    assert(2019 == data[4].load(std::memory_order_relaxed));
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
