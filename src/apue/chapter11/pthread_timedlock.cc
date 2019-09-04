#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

int FillTime(struct timespec* spec) {
    spec->tv_sec = 0;
#ifdef __APPLE__
    time(&spec->tv_sec);
#elif defined(__linux__)
    clock_gettime(CLOCK_REALTIME, spec);
#else
#error "unsuported plantform"
#endif
    struct tm * t = localtime(&spec->tv_sec);
    char buf[128] = {0};
    strftime(buf, sizeof(buf), "%r", t);
    printf("current time: %s\n", buf);
    return 0;
}

int main() {
#ifdef __linux__
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    printf("mutex is locked!\n");
    struct timespec spec;
    FillTime(&spec);
    spec.tv_sec += 2; // wait two seconds
    int ret = pthread_mutex_timedlock(&mutex, &spec);
    FillTime(&spec);
    if (ret == 0) {
        printf("mutex locked again!\n");
    } else {
        printf("can't lock mutex again: %s\n", strerror(ret));
    }
#else
    printf("plantform does not support pthread_mutex_timedlock!\n");
#endif
    return 0;
}
