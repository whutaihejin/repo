#include <iostream>
#include <thread>
#include <assert.h>
#include <atomic>

std::atomic<bool> x, y;
std::atomic<int> z;

void writeXthanY() {
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void readYthanX() {
    while (!y.load(std::memory_order_relaxed)) {
        // ignore
    }
    if (x.load(std::memory_order_relaxed)) {
        z.fetch_add(1, std::memory_order_seq_cst);
    }
}

int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(writeXthanY);
    std::thread b(readYthanX);
    a.join();
    b.join();
    assert(z.load(std::memory_order_seq_cst) != 0);
    return 0;
}
