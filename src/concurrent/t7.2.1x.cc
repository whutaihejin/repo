#include <iostream>
#include <thread>
#include <atomic>
#include <memory>

template <typename T> class LockfreeStack {
public:
    void Push(const T& data) {
        Node* node = new Node(data);
        node->next_ = head_.load();
        while (!head_.compare_exchange_weak(node->next_, node)) {
            // ignore
        }
    }

    std::shared_ptr<T> Pop() {
        Node* node = head_.load();
        while (node && !head_.compare_exchange_weak(node, node->next_)) {
            // ignore
        }
        return node ? node->data_ : NULL;
    }

private:
    struct Node {
        std::shared_ptr<T> data_;
        Node* next_;
        Node(const T& data): data_(std::make_shared<T>(data)) {}
    };

    std::atomic<Node*> head_;
};

LockfreeStack<int> stack;
const int limit = 10;
void Reader() {
    std::shared_ptr<int> p;
    for (int i = 0; i < limit;) {
        if ((p = stack.Pop())) {
            std::cout << *p << std::endl;
            ++i;
        }
    }
}

void Writer() {
    for (int i = 0; i < limit; ++i) {
        stack.Push(i + 1);
    }
}

int main() {
    std::thread t1(Reader);
    std::thread t2(Writer);
    t1.join();
    t2.join();
    return 0;
}
