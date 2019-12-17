#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void* RunTask(void* arg) {
    printf("A new thread start.\n"); // may be a cancellation point
    for (int i = 1; ; ++i) {
        // ignore
    }
    // not reached
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, RunTask, NULL);
    sleep(3);
    if (pthread_cancel(tid) != 0) {
        printf("cancel error\n");
        return -1;
    }
    void* status;
    printf("brefore join\n");
    pthread_kill(tid, SIGTERM);
    if (pthread_join(tid, &status) != 0) {
        printf("join error\n");
        return -1;
    }
    // not reached
    printf("after join\n");
    if (status == PTHREAD_CANCELED) {
        printf("Thread was cancelled.\n");
    } else {
        printf("Thread was not cancelled(should not hanppend).\n");
    }
    return 0;
}
