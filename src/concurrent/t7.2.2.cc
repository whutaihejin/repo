#include <iostream>
#include <thread>
#include <atomic>

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
        ++threads_in_pop_;
        Node* node = head_.load();
        while (node && !head_.compare_exchange_weak(node, node->next_)) {
            // ignore
        }
        std::shared_ptr<T> res;
        if (node) {
            res.swap(node->data_);
        }
        TryReclaim(node);
        return res;
    }
private:
    struct Node {
        T data_;
        Node* next_;
        Node(const T& data): data_(data) {}
    };

    void TryReclaim(Node* node) {
        if (threads_in_pop_ == 1) {
            Node* nodes_to_delete = to_be_deleted_.exchange(NULL);
            if (!--threads_in_pop_) {
                DeleteNodes(nodes_to_delete);
            } else if (nodes_to_delete) {
                ChainPendingNodes(nodes_to_delete);
            }
            delete node;
        } else {
            ChainPendingNode(node);
            --threads_in_pop_;
        }
    }
    
    static void DeleteNodes(Node* node) {
        while (node) {
            Node* next = node->next_;
            delete node;
            node = next;
        }
    }

    void ChainPendingNodes(Node* node) {
        Node* last = node;
        while (const Node* next = last->next_) {
            last = next;
        }
        ChainPendingNodes(node, last);
    }

    void ChainPendingNodes(Node* first, Node* last) {
        last->next_ = to_be_deleted_;
        while (!to_be_deleted_.compare_exchange_weak(last->next_, first)) {
            // ignore
        }
    }

    void ChainPendingNode(Node* node) {
        ChainPendingNodes(node, node);
    }

    // data member
    std::atomic<Node*> head_;
    std::atomic<int> threads_in_pop_;
    std::atomic<Node*> to_be_deleted_;
};

LockfreeStack<int> stack;
const int limit = 10;

void Reader() {
    for (int i = 0; i < limit;) {
        // ignore
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
