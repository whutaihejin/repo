#include <iostream>
#include <thread>

void Hello() {
    std::cout << "hello thread" << std::endl;
}

int main() {
    std::thread t(Hello);
    t.join();
    return 0;
}
