#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<bool> x, y;
std::atomic<int> z;

void WriteX() {
    x.store(true, std::memory_order_release);
}

void WriteY() {
    y.store(true, std::memory_order_release);
}

void ReadXThenY() {
    while (!x.load(std::memory_order_acquire)) {
        // ignore
    }
    if (y.load(std::memory_order_acquire)) {
        ++z;
    }
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
    std::thread t1(WriteX);
    std::thread t2(WriteY);
    std::thread t3(ReadXThenY);
    std::thread t4(ReadYThenX);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    assert(z.load() != 0);
    std::cout << "z = " << z.load() << std::endl;
    return 0;
}
