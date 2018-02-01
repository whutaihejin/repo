#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void WriteXThenY() {
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void ReadYThenX() {
    while (!y.load(std::memory_order_acquire)) {
        // ignore
    }
    if (x.load(std::memory_order_acquire)) {
        ++z;
    }
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread t2(ReadYThenX);
    std::thread t1(WriteXThenY);
    t1.join();
    t2.join();
    assert(z.load() != 0);
    std::cout << "z = " << z.load() << std::endl;
    return 0;
}
