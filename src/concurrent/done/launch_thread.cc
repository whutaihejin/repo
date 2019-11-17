#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

const int kTaskIteration = 3;
const int kInterval = 500;

// type 1: just a function
void Task() {
    for (int i = 0;  i < kTaskIteration; ++i) {
        std::cout << std::this_thread::get_id() << " -> " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(kInterval));
    }
}

// type 2: callable object
class CallableTask {
public:
    void operator()() const {
        for (int i = 0;  i < kTaskIteration; ++i) {
            std::cout << std::this_thread::get_id() << " -> " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(kInterval));
        }
    }
};

class FunTask {
public:
    FunTask(int& v): val_(v) {}

    void operator()() {
        for (int i = 0; i < 10; ++i) {
            std::cout << std::this_thread::get_id() << " xx -> " << val_ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(kInterval));
        }
    }

private:
    int& val_;
};

void BadFunc() {
    int local = 15;
    FunTask task(local);
    std::thread t(task);
    t.detach();
}

void GoodFunc() {
    int local = 286;
    FunTask task(local);
    std::thread t(task);
    t.join();
}

int main() {

    // type 1
    std::cout << "type 1" << std::endl;
    const int thread_num = 2;
    {
        std::vector<std::shared_ptr<std::thread>> thread_pool;
        for (int i = 0; i < thread_num; ++i) {
            thread_pool.push_back(std::make_shared<std::thread>(Task));
        }
        for (auto it = thread_pool.begin(); it != thread_pool.end(); ++it) {
            (*it)->join();
        }
    }
    
    // bad func
    BadFunc();
    // good func
    GoodFunc();
    
    // type 2
    std::cout << "type 2" << std::endl;
    {
        std::vector<std::shared_ptr<std::thread>> thread_pool;
        for (int i = 0; i < thread_num; ++i) {
            thread_pool.push_back(std::make_shared<std::thread>((CallableTask())));
        }
        for (auto it = thread_pool.begin(); it != thread_pool.end(); ++it) {
            (*it)->join();
        }
    }
    
    // type 3
    std::cout << "type 3" << std::endl;
    {
        std::vector<std::shared_ptr<std::thread>> thread_pool;
        for (int i = 0; i < thread_num; ++i) {
            thread_pool.push_back(std::make_shared<std::thread>([]() {
                for (int i = 0; i < kTaskIteration; ++i) {
                    std::cout << std::this_thread::get_id() << " -> " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(kInterval));
                }   
            }));
        }
        for (auto it = thread_pool.begin(); it != thread_pool.end(); ++it) {
            (*it)->join();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000000000));
    return 0;
}
