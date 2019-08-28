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
    pthread_create(&tid, nullptr, RunTask, nullptr);
    pthread_create(&tid2, nullptr, RunTask2, nullptr);
    // pthread_create((pthread_t*)&tids[1], nullptr, RunTask, &ids[1]);
    // pthread_create((pthread_t*)&tids[2], nullptr, RunTask, &ids[2]);
    // if (fork() == 0) {
    //     // do nothing
    //     printf("I am child process with %ld\n", (long)getpid());
    //     sleep(3);
    //     _exit(0);
    // } else {
    //     printf("I am parent process with %ld\n", (long)getpid());
    //     sleep(1);
    // }
    printf("I am parent process with %ld\n", (long)getpid());
    sleep(3);
    return 0;
}
