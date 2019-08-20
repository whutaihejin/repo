#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::vector<int> queue;
std::atomic<bool> flag(false);

void Reader() {
    while (!flag.load(std::memory_order_acquire)) {
        std::cout << 'w' << std::endl;
    }
    std::cout << queue[0] << std::endl;
}

void Writer() {
    queue.push_back(22);
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    flag.store(true, std::memory_order_release);
}

int main() {
    std::thread reader(Reader);
    std::thread writer(Writer);
    writer.join();
    reader.join();
    std::cout << "done" << std::endl;
    return 0;
}
