#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x(false), y(false);
std::atomic<int> z;

void writeXthanY() {
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
}

void readYthanX() {
    while (!y.load(std::memory_order_relaxed)) {
        // ignore
    }
    std::atomic_thread_fence(std::memory_order_acquire);
    if (x.load(std::memory_order_relaxed)) {
        ++z;
    }
}

int main() {
    z = 0;
    std::thread a(writeXthanY);
    std::thread b(readYthanX);
    a.join();
    b.join();
    assert(z.load() != 0);
    return 0;
}
