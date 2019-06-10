#include <iostream>
#include <pthread.h>
#include <deque>
#include <unistd.h>

class BlockingQueue {
public:
    BlockingQueue(const size_t capacity = 10000): capacity_(capacity) {
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&nonempty_cond_, NULL);
        pthread_cond_init(&nonfull_cond_, NULL);
    }
    ~BlockingQueue() {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&nonempty_cond_);
        pthread_cond_destroy(&nonfull_cond_);
    }

    void Push(int entry) {
        pthread_mutex_lock(&mutex_);
        while (queue_.size() > capacity_) {
            pthread_cond_wait(&nonfull_cond_, &mutex_);
        }
        queue_.push_back(entry);
        pthread_mutex_unlock(&mutex_);
        // send non empty signal
        pthread_cond_signal(&nonempty_cond_);
    }

    int Pop() {
        pthread_mutex_lock(&mutex_);
        while (queue_.empty()) {
            pthread_cond_wait(&nonempty_cond_, &mutex_);
        }
        int val = queue_.front();
        queue_.pop_front();
        pthread_mutex_unlock(&mutex_);
        // send non full signal
        pthread_cond_signal(&nonfull_cond_);
        return val;
    }

    size_t Capacity() {
        return capacity_;
    }

    void SetCapacity(size_t capacity) {
        capacity_ = capacity;
    }

private:
    std::atomic<size_t> capacity_;
    std::deque<int> queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t nonempty_cond_;
    pthread_cond_t nonfull_cond_;
};


// global mutex for std::cout
pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;
struct TaskMeta {
    TaskMeta(): exit(false), queue(NULL) {}
    bool Exit() {
        return exit;
    }

    void SetExit(bool val) {
        exit = val;
    }

    std::atomic<bool> exit;
    BlockingQueue* queue;
};

void* Task(void* args) {
    TaskMeta* meta = static_cast<TaskMeta*>(args);
    BlockingQueue* queue = meta->queue;
    // consumer task
    while (!meta->Exit()) {
        // usleep(1000);
        int val = queue->Pop();
        pthread_mutex_lock(&cout_mutex);
        std::cout << "take an element " << val << std::endl;
        pthread_mutex_unlock(&cout_mutex);
    }
    pthread_mutex_lock(&cout_mutex);
    std::cout << "exit the task thread!" << std::endl;
    pthread_mutex_unlock(&cout_mutex);
    return NULL;
}

int main() {
    BlockingQueue queue;
    TaskMeta task_meta;
    task_meta.queue = &queue;

    pthread_t tid;
    if (pthread_create(&tid, NULL, Task, static_cast<void*>(&task_meta)) != 0) {
        std::cout << "create pthread failed!" << std::endl;
        return -1;
    }
    // producer task
    for (int i = 0; i < 1000; ++i) {
        queue.Push(i + 1);
        pthread_mutex_lock(&cout_mutex);
        std::cout << "push queue " << (i + 1) << std::endl;
        pthread_mutex_unlock(&cout_mutex);
    }
    // size_t i = 0;
    // while (true) { queue.Push(i++); }
    task_meta.SetExit(true);
    pthread_join(tid, NULL);
    std::cout << "join done, exit the main thread!" << std::endl;
}
