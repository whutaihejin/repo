#include <thread>
#include <iostream>

void Task1() {
    for (int i = 0; i < 10; i++) {
        std::cout << i << " --> Task1" << std::endl;
    }
}

class Task2 {
public:
    void operator()() const {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << " --> Task2" << std::endl;
        }
    }
};

class Task3 {
public:
    Task3(int& val): val_(val) {}

    void operator() () {
        for (unsigned int j = 0; j < 1000000; ++j) {
            std::cout << j << std::endl;
        }
        std::cout << std::endl;
    }
private:
    int val_;
};

void Fun() {
    int val = 1;
    Task3 task3(val);
    std::thread thread(task3);
    // thread.detach();
    thread.join();
}

int main() {
    Fun();
    
    //
    std::thread thread1(Task1);
    thread1.join();
    
    //
    std::cout << "-------" << std::endl;
    Task2 task2;
    std::thread thread2(task2);
    thread2.join();

    std::cout << "-------" << std::endl;
    // parentheses were disambiguated as a function declaration (FixIt)
    // std::thread thread3(Task2());
    std::thread thread3((Task2()));
    thread3.join();

    std::cout << "-------" << std::endl;
    std::thread thread4{Task2()};
    thread4.join();

    std::cout << "-------" << std::endl;
    std::thread thread5([](){
            for (int i = 0; i < 10; ++i) {
                std::cout << i << " --> Task5" << std::endl;
            }
         });
    thread5.join();

    return 0;
}
