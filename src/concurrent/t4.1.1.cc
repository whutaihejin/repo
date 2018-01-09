#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
std::condition_variable condition;

struct Request {
    int val;
    int flag;
};

Request request{0, 0};

void Task1() {
    for (;;) {
        std::lock_guard<std::mutex> guard(mutex);
        int limit = request.val + 10;
        for (; request.val < limit; ++request.val) {
            std::cout << std::this_thread::get_id() << " ****** --> " << request.val << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        request.flag = 1;
        condition.notify_one();
    }
}

void Task2() {
    for (;;) {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, []() { return request.flag; });
        request.flag = 0;
        int limit = request.val + 10;
        for (; request.val < limit; ++request.val) {
            std::cout << std::this_thread::get_id() << " $$$$$$ --> " << request.val << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::thread thread2(Task2);
    std::thread thread1(Task1);
    thread1.join();
    thread2.join();
    return 0;
}
