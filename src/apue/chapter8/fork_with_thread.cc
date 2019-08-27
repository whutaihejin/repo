#include <stdio.h>
#include <pthread.h>
#include <atomic>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

std::atomic<bool> stop(false);

void* RunTask(void *arg) {
    while (!stop.load(std::memory_order_acquire)) {
        printf("pthread task %ld, %ld\n", (long)getpid(), (long)getppid());
    }
    return nullptr;
}

int main() {
    std::vector<int> ids{11, 22, 33};
    std::vector<pthread_t> tids[3];
    pthread_create((pthread_t*)&tids[0], nullptr, RunTask, &ids[0]);
    // pthread_create((pthread_t*)&tids[1], nullptr, RunTask, &ids[1]);
    // pthread_create((pthread_t*)&tids[2], nullptr, RunTask, &ids[2]);
    if (fork() == 0) {
        // do nothing
    } else {
        sleep(1);
        stop.store(true, std::memory_order_release);
        printf("parent exit with %ld\n", (long)getpid());
    }
    return 0;
}
