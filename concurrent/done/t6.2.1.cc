#include <iostream>
#include <thread>
#include <stack>
#include <mutex>

template <typename T> class ThreadsafeStack {
public:
    ThreadsafeStack() {}
    
    ThreadsafeStack(const ThreadsafeStack& stack) {
        std::lock_guard<std::mutex> lock(stack.m);
        data_ = stack.data_;
    }

    ThreadsafeStack& operator=(const ThreadsafeStack&) = delete;

    void Push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_.push(std::move(value));
    }

    std::shared_ptr<T> Pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_.empty()) {
            return NULL;
            // return std::make_shared<T>();
        }
        const std::shared_ptr<T> ref(std::make_shared<T>(std::move(data_.top())));
        data_.pop();
        return ref;
    }

    void Pop(T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_.empty()) {
            throw std::runtime_error("empty stack");
        }
        value = std::move(data_.top());
        data_.pop();
    }

    bool Empty() {
        std::lock_guard<T> lock(mutex_);
        return data_.empty();
    }

private:
    std::stack<T> data_;
    mutable std::mutex mutex_;

};

void TaskInput(ThreadsafeStack<int>& stack, int limit) {
    for (int i = 0; i < limit; ++i) {
        stack.Push(i);
    }
}

void TaskOutput(ThreadsafeStack<int>& stack, int limit) {
    int count = 0;
    for (;;) {
        std::shared_ptr<int> top = stack.Pop();
        if (top) {
            std::cout << *top << " ";
            if (++count == limit) {
                break;
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    const int limit = 20;
    ThreadsafeStack<int> stack;
    auto it = stack.Pop();
    if (it) {
        std::cout << "not empty " << *it << std::endl;
    } else {
        std::cout << "empty" << std::endl;
    }
    std::thread input(TaskInput, std::ref(stack), limit);
    std::thread output(TaskOutput, std::ref(stack), limit);
    input.join();
    output.join();
    return 0;
}
