#include <iostream>
#include <future>
#include <thread>

// task of get info from redis
int FetchRedis();
// task of get address from mysql
int FetchMysql();

int main() {
    auto start = std::chrono::system_clock::now();
    // two tasks
    std::future<int> info = std::async(FetchRedis);
    std::future<int> address = std::async(FetchMysql);
    std::cout << "info => " << info.get() << std::endl;
    std::cout << "address => " << address.get() << std::endl;

    // record time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "spent time: " << diff.count() << " s\n";
    return 0;
}

int FetchRedis() {
    std::chrono::seconds sec(2);
    std::this_thread::sleep_for(sec);
    return 13;
}

int FetchMysql() {
    std::chrono::seconds sec(1);
    std::this_thread::sleep_for(sec);
    return 12;
}
