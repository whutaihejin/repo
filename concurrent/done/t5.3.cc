#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void ReadThread() {
    while (!data_ready.load()) {
      std::cout << "test --begin" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      std::cout << "test --end" << std::endl;
    }
    std::cout << "The answer = " << data[0] << std::endl;
}

void WriteThread() {
    data.push_back(1);
    data_ready.store(true);
}

int main() {
    std::thread reader(ReadThread);
    std::thread writer(WriteThread);
    reader.join();
    writer.join();
    return 0;
}
