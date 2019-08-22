#include <thread>
#include <atomic>
#include <assert.h>
#include <iostream>

std::atomic<int> x(0), y(0), z(0);
std::atomic<bool> go(false);

unsigned const loop_count = 10;

struct readValues {
    int x, y, z;
};

readValues v1[loop_count];
readValues v2[loop_count];
readValues v3[loop_count];
readValues v4[loop_count];
readValues v5[loop_count];

void increment(std::atomic<int>* var, readValues* val) {
    while (!go) {
        std::this_thread::yield();
    }
    for (unsigned int i = 0; i < loop_count; ++i) {
        val[i].x = x.load(std::memory_order_relaxed);
        val[i].y = y.load(std::memory_order_relaxed);
        val[i].z = z.load(std::memory_order_relaxed);
        var->store(i + 1, std::memory_order_relaxed);
        std::this_thread::yield();
    }
}

void read(readValues* val) {
    while (!go) {
        std::this_thread::yield();
    }
    for (unsigned int i = 0; i < loop_count; ++i) {
        val[i].x = x.load(std::memory_order_relaxed);
        val[i].y = y.load(std::memory_order_relaxed);
        val[i].z = z.load(std::memory_order_relaxed);
        std::this_thread::yield();
    }
}

void Print(readValues* v) {
    for (unsigned int i = 0; i < loop_count; ++i) {
        if (i) {
            std::cout << ",";
        }
        std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
    }
    std::cout << std::endl;
}

int main() {
    std::thread t1(increment, &x, v1);
    std::thread t2(increment, &y, v2);
    std::thread t3(increment, &z, v3);
    std::thread t4(read, v4);
    std::thread t5(read, v5);

    go = true;
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    
    Print(v1);
    Print(v2);
    Print(v3);
    Print(v4);
    Print(v5);
    return 0;
}
