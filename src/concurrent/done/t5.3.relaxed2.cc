#include <iostream>
#include <thread>
#include <atomic>
#include <assert.h>

std::atomic<int> x(0), y(0), z(0);
std::atomic<bool> go(false);

size_t const limit = 10;

struct ReadValues {
    int x;
    int y;
    int z;
};

ReadValues v1[limit];
ReadValues v2[limit];
ReadValues v3[limit];
ReadValues v4[limit];
ReadValues v5[limit];

void Increment(std::atomic<int>* var, ReadValues* read_val) {
    while (!go.load()) {
        std::this_thread::yield();
    }
    for (size_t i = 0; i < limit; ++i) {
        read_val[i].x = x.load(std::memory_order_relaxed);
        read_val[i].y = y.load(std::memory_order_relaxed);
        read_val[i].z = z.load(std::memory_order_relaxed);
        var->store(i + 1, std::memory_order_relaxed);
        std::this_thread::yield();
    }
}

void ReadVals(ReadValues* val) {
    while (!go.load()) {
        std::this_thread::yield();
    }
    for (size_t i = 0; i < limit; ++i) {
        val[i].x = x.load(std::memory_order_relaxed);
        val[i].y = y.load(std::memory_order_relaxed);
        val[i].z = z.load(std::memory_order_relaxed);
        std::this_thread::yield();
    }
}

void Print(ReadValues* val) {
    for (size_t i = 0; i < limit; ++i) {
        if (i)  {
            std::cout << ",";
        }
        std::cout << "(" << val[i].x << "," << val[i].y << "," << val[i].z << ")";
    }
    std::cout << std::endl;
}

int main() {
    std::thread t1(Increment, &x, v1);
    std::thread t2(Increment, &y, v2);
    std::thread t3(Increment, &z, v3);
    std::thread t4(ReadVals, v4);
    std::thread t5(ReadVals, v5);
    go.store(true);
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
