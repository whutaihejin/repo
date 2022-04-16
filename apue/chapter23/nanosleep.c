#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

void Handler(int sig) {
    printf("c %d\n", sig);
}

int main() {
    struct timeval start, finish;
    struct timespec request, remain;

    request.tv_sec = 10;
    request.tv_nsec = 0;

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = Handler;
    sigaction(SIGINT, &act, NULL);

    gettimeofday(&start, NULL);

    for (;;) {
        int s = nanosleep(&request, &remain);
        if (s == -1 && errno != EINTR) {
            printf("nanosleep error"), exit(1);
        }
        gettimeofday(&finish, NULL);
        printf("sleep for: %9.6f secs\n", finish.tv_sec - start.tv_sec + (finish.tv_usec - start.tv_usec) / 1E6);
        if (s == 0) {
            break;
        }

        printf("remaining %2ld.%09ld\n", remain.tv_sec, remain.tv_nsec);
        request = remain;
    }
    printf("sleep complete\n");
    return 0;
}
