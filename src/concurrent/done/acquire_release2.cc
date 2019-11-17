#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void writeXthanY() {
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_release);
}

void readYthanX() {
    while (!y.load(std::memory_order_acquire)) {
        // ignore
    }
    if (x.load(std::memory_order_relaxed)) {
        ++z;
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
    assert(z.load() != 0);
}
