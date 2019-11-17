#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

const size_t thread_num = 100;
const int64_t limit = 1000000;

// for task1
std::mutex mu;
int64_t total = 0;

// for task2
std::atomic<std::int64_t> atomic_total(0);
// std::atomic_int64_t atomic_total = 0;

void Task1() {
    for (int64_t i = 0; i < limit; ++i) {
        mu.lock();
        ++total;
        mu.unlock();
    }
}

void Task2() {
    for (int64_t i = 0; i < limit; ++i) {
        ++atomic_total;
    }
}

int main() {
    std::vector<std::thread> thread_pool;
    for (int i = 0; i < thread_num; ++i) {
        thread_pool.push_back(std::thread(Task2));
    }
    //
    for (auto it = thread_pool.begin(); it != thread_pool.end(); ++it) {
        it->join();
    }
    std::cout << "total is " << atomic_total << std::endl;
}



// version one
// void Task(int64_t& sum) {
//     int64_t val = 0;
//     for (int64_t i = 0; i < limit; ++i) {
//         val += 1;
//     }
//     sum = val;
// }
// 
// int main() {
//     int thread_num = 3;
//     std::vector<int64_t> seq(thread_num);
//     for (auto it = seq.begin(); it != seq.end(); ++it) {
//         std::cout << (*it) << std::endl;
//     }
//     std::vector<std::thread> thread_pool;
//     for (int i = 0; i < thread_num; ++i) {
//         thread_pool.push_back(std::thread(Task, std::ref(seq[i])));
//     }
//     //
//     for (auto it = thread_pool.begin(); it != thread_pool.end(); ++it) {
//         it->join();
//     }
// 
//     // cal all sum
//     int64_t total = 0;
//     for (auto it = seq.begin(); it != seq.end(); ++it) {
//         total += (*it);
//     }
//     std::cout << "sum is " << total << std::endl;
// }
