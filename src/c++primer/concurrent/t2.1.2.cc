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

int main() {
    std::thread thread((Task()));
    std::cout << "-----" << thread.joinable() << std::endl;
    thread.join();
    std::cout << "-----" << thread.joinable() << std::endl;
    return 0;
}
