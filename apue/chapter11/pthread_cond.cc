#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <deque>

#include "pthread_mutex.h"

template<class T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity): 
        capacity_(capacity),
        notfull_cond_(&mutex_),
        notempty_cond_(&mutex_) {}

    void Put(const T& v) {
        mutex_.Lock();
        while (queue_.size() >= capacity_) {
            notfull_cond_.Wait();
        }
        queue_.push_back(v);
        mutex_.Unlock();
        notempty_cond_.Signal();
    }

    T& Poll() {
        mutex_.Lock();
        while (queue_.empty()) {
            notempty_cond_.Wait();
        }
        T& v = queue_.front();
        queue_.pop_front();
        mutex_.Unlock();
        notfull_cond_.Signal();
        return v;
    }

private:
    size_t capacity_;
    Mutex mutex_;
    Condition notfull_cond_;
    Condition notempty_cond_;
    std::deque<T> queue_;
};

struct TaskContext {
    size_t limit;
    BlockingQueue<int>* queue;
};

void* Producer(void* arg) {
    struct TaskContext* context = (struct TaskContext*)arg;
    for (size_t i = 0; i < context->limit; ++i) {
        context->queue->Put(rand() % 100);
    }
    return (void*)0;
}

int main() {
    BlockingQueue<int> queue(128);
    TaskContext context;
    context.limit = 100;
    context.queue = &queue;

    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, Producer, (void*)&context);
    pthread_create(&tid2, nullptr, Producer, (void*)&context);

    for (int i = 0; i < 2 * context.limit; ++i) {
        int v = queue.Poll();
        printf("->%d ", v);
        if ((i + 1) % 20 == 0) printf("\n");
    }
    return 0;
}
