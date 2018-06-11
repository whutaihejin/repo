#include <iostream>
#include <algorithm>

template<typename T> class Stack {
public:
    explicit Stack<T>(const int capacity = 10):
        top_(-1),
        capacity_(capacity) {
            capacity_ = std::max<int>(1, capacity_);
            stack_ = new T[capacity_];
        }

    int Push(const T& t) {
        if (top_ + 1 >= capacity_) {
            // overflow
            return -1;
        }
        stack_[++top_] = t;
        return 0;
    }

    T& Pop() {
        if (top_ < 0) {
            // underflow, throw expection
            throw std::underflow_error("exception: empty stack");
        }
        T& t = stack_[top_--];
        return t;
    }

    ~Stack<T> () {
        delete[] stack_;
    }

private:
    int top_;
    int capacity_;
    T* stack_;
};

int main() {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    std::cout << stack.Pop() << std::endl;
    std::cout << stack.Pop() << std::endl;
    try {
    std::cout << stack.Pop() << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
