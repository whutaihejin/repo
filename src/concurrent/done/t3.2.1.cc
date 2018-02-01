#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>

std::list<int> cars;
std::mutex cars_mutext;

void AddCar(int car) {
    std::lock_guard<std::mutex> guard(cars_mutext);
    cars.push_back(car);
}

bool Contains(int car) {
    std::lock_guard<std::mutex> guard(cars_mutext);
    return std::find(cars.cbegin(), cars.cend(), car) != cars.cend();
}

void Task() {
    for (int i = 0; i < 10; ++i) {
        AddCar(i);
    }
}

int main() {
    std::thread thread1(Task);
    std::thread thread2(Task);
    thread1.join();
    thread2.join();
    for (auto it = cars.cbegin(); it != cars.cend(); ++it) {
        std::cout << *it  << " ";
    }
    std::cout << std::endl;
    return 0;
}
