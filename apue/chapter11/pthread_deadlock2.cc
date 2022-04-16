#include <stdio.h>
#include <unistd.h>

#include "pthread_mutex.h"

Mutex m1;
Mutex m2;

void* StartTask(void *arg) {
    m1.Lock();
    sleep(1);
    m2.Lock();
    return (void*)1;
}

void* StartTask2(void *arg) {
    m2.Lock();
    sleep(1);
    m1.Lock();
    return (void*)1;
}


int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, StartTask, nullptr);
    pthread_create(&tid2, nullptr, StartTask2, nullptr);
    void *ret;
    pthread_join(tid1, &ret);
    pthread_join(tid2, &ret);
    return 0;
}
