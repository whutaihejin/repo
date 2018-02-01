#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

template <typename T> class LockfreeStack {
public:
    void Push(const T& data) {
        Node* node = new Node(data);
        node->next_ = head_.load();
        while (!head_.compare_exchange_weak(node->next_, node)) {
            // ignore
        }
    }

    int Pop(T& val) {
        Node* node = head_.load();
        if (node == NULL) {
            return -1;
        }
        while (!head_.compare_exchange_weak(node, node->next_)) {
            // ignore
        }
        return node ? (val = node->data_), 0 : -1;
    }
private:
    struct Node {
        T data_;
        Node* next_;
        Node(const T& data): data_(data) {}
    };
    std::atomic<Node*> head_;
};

LockfreeStack<int> stack;
const int limit = 10;

void Reader() {
    int val = 0;
    for (int i = 0; i < limit;) {
        if (stack.Pop(val) == 0) {
            std::cout << val << std::endl;
            ++i;
        }
    }
}

void Writer() {
    for (int i = 0; i < limit; ++i) {
        stack.Push(i);
    }
}

int main() {
    std::thread t1(Reader);
    std::thread t2(Writer);
    t1.join();
    t2.join();
    return 0;
}
