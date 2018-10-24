#include <iostream>
#include <thread>

void Task() {
    std::cout << "thread task" << std::endl;
}

void Fun() {
    std::thread t(Task);
    try {
    // do something and throw exception
    throw std::exception();
    } catch (...) {
        std::cout << "catch exception" << std::endl;
        t.join();
        return;
    }
    t.join();
}

class Guard {
public:
    explicit Guard(std::thread& t): thread_(t) {}

    // destroy
    ~Guard() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    // forbidden copy and assign
    Guard(const Guard&) =  delete;
    Guard& operator=(const Guard&) = delete;

    // data member
    std::thread& thread_;
};

void Good() {
    std::thread t(Task);
    Guard g(t);
    throw std::exception();
}

int main() {
    Fun();
    try {
        Good();
    } catch (...) {
       // ignore 
    }
    return 0;
}
