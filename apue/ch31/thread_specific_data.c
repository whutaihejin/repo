#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t trace_key;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void done();

void DestroyTraceKey(void* trace) {
    printf("I am destory.\n");
    int* key = (int*)trace;
    free(key);
}

void InitTraceKey() {
    printf("I am init.\n");
    pthread_key_create(&trace_key, DestroyTraceKey);
}

void process() {
    printf("I am process. tid=%ld\n", (long)pthread_self());
    int* trace = (int*)pthread_getspecific(trace_key);
    if (trace) {
        printf("process: tid=%ld, trace=%d\n", (long)pthread_self(), *trace);
    } else {
        printf("no trace=\n");
    }
    done();
}

void done() {
    printf("I am done. tid=%ld\n", (long)pthread_self());
    int* trace = (int*)pthread_getspecific(trace_key);
    if (trace) {
        printf("done: tid=%ld, trace=%d\n", (long)pthread_self(), *trace);
    } else {
        printf("no trace=\n");
    }
}

void* RunTask(void* arg) {
    pthread_once(&once_control, InitTraceKey);
    void *trace;
    if ((trace = pthread_getspecific(trace_key)) == NULL) {
        trace = malloc(sizeof(int));
        pthread_setspecific(trace_key, trace);
    }
    // assign trace
    (*(int*)trace) = *(int*)arg;
    // next func
    process();
    return NULL;
}

int main() {
    int trace1 = 11, trace2 = 22;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, RunTask, &trace1);
    pthread_create(&tid2, NULL, RunTask, &trace2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
