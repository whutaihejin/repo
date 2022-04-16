#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void WriteX() {
    x.store(true, std::memory_order_seq_cst);
}

void WriteY() {
    y.store(true, std::memory_order_seq_cst);
}

void ReadXThenY() {
    while (!x.load(std::memory_order_seq_cst)) {
        // ignore
    }
    if (y.load(std::memory_order_seq_cst)) {
        ++z;
    }
}

void ReadYThenX() {
    while (!y.load(std::memory_order_seq_cst)) {
        // ignore
    }
    if (x.load(std::memory_order_seq_cst)) {
        ++z;
    }
}
int main() {
    x = false;
    y = false;
    z = 0;
    std::thread a(WriteX);
    std::thread b(WriteY);
    std::thread c(ReadXThenY);
    std::thread d(ReadYThenX);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0);
    std::cout << "z.load()=" << z.load() << std::endl;
    return 0;
}
