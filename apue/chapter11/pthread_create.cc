#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

void PrintThread(const char* str) {
    pthread_t tid = pthread_self();
    printf("%s pid %lu tid %lu(0x%lx)\n", str, (long)getpid(), (unsigned long)tid, (unsigned long)tid);
}

void *TaskStart(void *arg) {
    PrintThread("new thread:");
    return (void*)nullptr;
}

int main() {
    pthread_t tid;
    if (pthread_create(&tid, nullptr, TaskStart, nullptr) != 0) {
    }
    PrintThread("main thread:");
    sleep(1);
    assert(pthread_equal(pthread_self(), pthread_self()) != 0);
    assert(tid != pthread_self());
    return 0;
}
