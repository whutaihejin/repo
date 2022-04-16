#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void writeX() {
    x.store(true, std::memory_order_release);
}

void writeY() {
    y.store(true, std::memory_order_release);
}

void readXthanY() {
    while (!x.load(std::memory_order_acquire)) {
        // ignore
    }
    if (y.load(std::memory_order_acquire)) {
        ++z;
    }
}

void readYthanX() {
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
    std::thread a(writeX);
    std::thread b(writeY);
    std::thread c(readXthanY);
    std::thread d(readYthanX);
    a.join();
    b.join();
    c.join();
    d.join();
    // z.store(0);
    assert(z.load() != 0);
    return 0;
}
