#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int main() {
    struct timespec spec;
    struct timespec res;

    if (clock_gettime(CLOCK_REALTIME, &spec) == 0) {
        printf("spec: %2ld.%09ld\n", spec.tv_sec, spec.tv_nsec);
    }
    if (clock_getres(CLOCK_REALTIME, &res) == 0) {
        printf("res: %2ld.%09ld\n", res.tv_sec, res.tv_nsec);
    }
   
    // CLOCK_MONOTONIC
    if (clock_gettime(CLOCK_MONOTONIC, &spec) == 0) {
        printf("MONOTONIC: %2ld.%09ld\n", spec.tv_sec, spec.tv_nsec);
    }
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec) == 0) {
        printf("CLOCK_PROCESS_CPUTIME_ID: %2ld.%09ld\n", spec.tv_sec, spec.tv_nsec);
    }
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &spec) == 0) {
        printf("CLOCK_THREAD_CPUTIME_ID: %2ld.%09ld\n", spec.tv_sec, spec.tv_nsec);
    }

    clockid_t clockid;
    if (clock_getcpuclockid(getpid(), &clockid) == 0) {
        if (clock_gettime(clockid, &spec) == 0) {
            printf("process %lu: %2ld.%09ld\n", (long)clockid, spec.tv_sec, spec.tv_nsec);
        }
    }
    if (pthread_getcpuclockid(pthread_self(), &clockid) == 0) {
        if (clock_gettime(clockid, &spec) == 0) {
            printf("pthread %lu: %2ld.%09ld\n", (long)clockid, spec.tv_sec, spec.tv_nsec);
        }
    }
    return 0;
}
