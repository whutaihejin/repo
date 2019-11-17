#include <atomic>
#include <thread>
#include <assert.h>
#include <string>

struct Entry {
    int val;
    std::string name;
};

std::atomic<Entry*> ptr;
std::atomic<int> a;

void createEntry() {
    Entry* e = new Entry;
    e->val = 22;
    e->name = "hello";
    a.store(99, std::memory_order_relaxed);
    ptr.store(e, std::memory_order_consume);
}

void useEntry() {
    Entry* e;
    while (!(e = ptr.load(std::memory_order_consume))) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        // std::this_thread::sleep(std::chrono::microseconds(1));
    }
    assert(e->val == 22);
    assert(e->name == "hello");
    assert(a.load(std::memory_order_relaxed) == 99);
}

int main() {
    std::thread t1(createEntry);
    std::thread t2(useEntry);
    t1.join();
    t2.join();
    return 0;
}
