#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>


void* RunTask(void *arg) {
    fork();
    for (int i = 0; i < 3; ++i) {
        printf("pthread task %ld, %ld\n", (long)getpid(), (long)getppid());
    }
    return nullptr;
}

void* RunTask2(void *arg) {
    for (int i = 0; i < 3; ++i) {
        printf("just shit it! pthread task %ld, %ld\n", (long)getpid(), (long)getppid());
    }
    return nullptr;
}

int main() {
    pthread_t tid, tid2;
    // common thread
    pthread_create(&tid2, nullptr, RunTask2, nullptr);
    // fork within this thread
    pthread_create(&tid, nullptr, RunTask, nullptr);
    // parent show
    printf("I am parent process with %ld\n", (long)getpid());
    sleep(3);
    return 0;
}
