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

std::mutex bus_mutex;
std::condition_variable bus_condition;
int station_arrived = 0;

void TaskSeller() {
    for (;;) {
        std::unique_lock<std::mutex> lock(bus_mutex);
        bus_condition.wait(lock, []() { return station_arrived == 1; });
        std::cout << std::this_thread::get_id() << " seller seller done" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        station_arrived = 0;
        bus_condition.notify_one();
    }
}

void TaskDriver() {
    for (;;) {
        std::unique_lock<std::mutex> lock(bus_mutex);
        bus_condition.wait(lock, []() { return station_arrived == 0; });
        std::cout << std::this_thread::get_id() << " driver driver done" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        station_arrived = 1;
        bus_condition.notify_one();
    }
}

int main() {
    std::thread thread2(TaskSeller);
    std::thread thread1(TaskDriver);
    thread1.join();
    thread2.join();
    return 0;
}
