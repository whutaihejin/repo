#include <thread>
#include <iostream>

class Task {
public:
    void operator() () {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << std::endl;
        }
    }
};

// Resource Acquisition Is Initialization -> RAII
static int count = 1;
class TaskGuard {
public:
    explicit TaskGuard(std::thread& thread): thread_(thread) {}

    // forbidden copy and assignment
    TaskGuard(const TaskGuard&) = delete;
    TaskGuard& operator=(const TaskGuard&) = delete;

    ~TaskGuard() {
        count += 1;
        if (thread_.joinable()) {
            std::cout << "invoke join" << std::endl;
            thread_.join();
        }
    }

private:
    std::thread& thread_;
};

void Bad() {
    throw std::runtime_error("bad");
}

void Fun() {
    std::thread thread((Task()));
    // libc++abi.dylib: terminating with uncaught exception of type std::runtime_error: bad
    Bad();
    thread.join();
}

void Good() {
    std::thread thread((Task()));
    try {
        Bad();
    } catch (...) {
        thread.join();
        return;
        // throw;
    }
    thread.join();
}

void Perfect() {
    std::thread thread((Task()));
    TaskGuard guard(thread);
    Bad();
}

int main() {
    // Fun();
    Good();
    std::cout << "------" << std::endl;
    Perfect();
    return 0;
}
