#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <pthread.h>
#include <stdlib.h>

void DoCommand(char* cmd);

static long GetTick();

int main(int argc, char* argv[]) {
    struct tms tms_start, tms_end;
    clock_t start, end;

    start = times(&tms_start);
    for (int i = 1; i < argc; ++i) {
        DoCommand(argv[i]);
    }
    end = times(&tms_end);

    printf("real time = %ld\n", (end - start) / GetTick());
    return 0;
}

static long clock_tick = 0;
static pthread_once_t tick_once = PTHREAD_ONCE_INIT;

static void InitTick() {
    clock_tick = sysconf(_SC_CLK_TCK);
}

static long GetTick() {
    pthread_once(&tick_once, InitTick);
    return clock_tick;
}

void DoCommand(char* cmd) {
    system(cmd);
}
