#include <stdio.h>

#include "pthread_mutex.h"

// shared count
int count = 0;
size_t limit = 1000000;

void *IncrTask(void* arg) {
    for (size_t i = 0; i < limit; ++i) {
        // LockGuard l((Mutex*)arg);
        ++count;
    }
    pthread_exit((void*)nullptr);
}

int main() {
    //
    pthread_t tid1, tid2;
    Mutex mutex;
    pthread_create(&tid1, nullptr, IncrTask, &mutex);
    pthread_create(&tid2, nullptr, IncrTask, &mutex);
    void *ret;
    pthread_join(tid1, (void**)&ret);
    printf("thread 1 exit code %ld\n", (long)ret);
    
    pthread_join(tid2, (void**)&ret);
    printf("thread 2 exit code %ld\n", (long)ret);

    // result
    printf("count result: %d\n", count);
    return 0;
}
