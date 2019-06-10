#include <iostream>
#include <pthread.h>

class BlockingQueue {
public:
    BlockingQueue(): exit_(false) {}

    bool Exit() {
        return exit_;
    }
    void SetExit(bool val) {
        exit_ = val;
    }

private:
    std::atomic<bool> exit_;
};


// global mutex for std::cout
pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;

void* Task(void* args) {
    BlockingQueue* queue = static_cast<BlockingQueue*>(args);
    while (!queue->Exit()) {
        pthread_mutex_lock(&cout_mutex);
        std::cout << "take an element" << std::endl;
        pthread_mutex_unlock(&cout_mutex);
    }
    pthread_mutex_lock(&cout_mutex);
    std::cout << "exit the task thread!" << std::endl;
    pthread_mutex_unlock(&cout_mutex);
    return NULL;
}

int main() {
    BlockingQueue queue;
    pthread_t tid;
    if (pthread_create(&tid, NULL, Task, static_cast<void*>(&queue)) != 0) {
        std::cout << "create pthread failed!" << std::endl;
        return -1;
    }
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&cout_mutex);
        std::cout << "push queue " << (i + 1) << std::endl;
        pthread_mutex_unlock(&cout_mutex);
    }
    queue.SetExit(true);
    pthread_join(tid, NULL);
    std::cout << "join done, exit the main thread!" << std::endl;
}
