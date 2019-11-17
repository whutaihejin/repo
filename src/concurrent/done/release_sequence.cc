#include <atomic>
#include <thread>
#include <assert.h>
#include <vector>
#include <iostream>

std::vector<int> queue;
std::atomic<int> count;

void populateQueue() {
    unsigned int const num_items = 9;
    queue.clear();
    for (unsigned int i = 0; i < num_items; ++i) {
        queue.push_back(i);
    }
    count.store(num_items, std::memory_order_release);
}

void consumeQueue() {
    while (true) {
        int index;
        // if ((index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) {
        if ((index = count.fetch_sub(1, std::memory_order_relaxed)) <= 0) {
            std::this_thread::yield();
            continue;
        }
        std::cout << index << std::endl;
    }
}

int main() {
    std::thread a(populateQueue);
    std::thread b(consumeQueue);
    std::thread c(consumeQueue);
    a.join();
    b.join();
    c.join();
    return 0;
}
