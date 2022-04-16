#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void WriteXThenY() {
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
}

void ReadYThenX() {
    while (!y.load(std::memory_order_relaxed)) {
        // ignore
    }
    std::atomic_thread_fence(std::memory_order_acquire);
    if (x.load(std::memory_order_relaxed)) {
        ++z;
    }
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread t1(WriteXThenY);
    std::thread t2(ReadYThenX);
    t1.join();
    t2.join();
    assert(z.load() != 0);
    std::cout << "z = " << z.load() << std::endl;
    return 0;
}
