#include <iostream>
#include <algorithm>

template<typename T> class Queue {
public:
    explicit Queue<T>(const int capacity = 10):
        capacity_(capacity),
        head_(0),
        tail_(0) {
            // at least one element
            capacity_ = std::max(capacity_, 1);
            queue_ = new T[capacity_];
        }

    int Enqueue(const T& t) {
        int next = (tail_ + 1) % capacity_;
        if (next == head_) {
            throw std::overflow_error("exception: overflow");
            return -1;
        }
        queue_[tail_] = t;
        tail_ = next;
        return 0;
    }

    int Dequeue() {
        if (head_ == tail_) {
            throw std::underflow_error("exception: underflow");
            return -1;
        }
        T& t = queue_[head_];
        head_ = (head_ + 1) % capacity_;
        return t;
    }

    ~Queue() {
        delete[] queue_;
    }
private:
    int capacity_;
    int head_;
    int tail_;
    T* queue_;
};

int main() {
    Queue<int> queue(11);
    try {
        for (int i = 1; i <= 12; i++) {
            queue.Enqueue(i);
        }
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        for (int i = 1; i <= 12; i++) {
            std::cout << queue.Dequeue() << std::endl;
        }
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
