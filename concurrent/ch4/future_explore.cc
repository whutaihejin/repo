#include <iostream>
#include <future>

int CountFile() {
    return 1;
}

int main() {
    std::future<int> answer = std::async(CountFile);
    std::cout << "The answer is " << answer.get() << std::endl;
    return 0;
}
