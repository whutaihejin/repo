#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t got_alarm = 0;

void DisplayTimes(const char* msg, int include_timer) {
    struct timeval cur;
    
    // static members
    static int call_num = 0;
    static struct timeval start;
    if (call_num == 0) {
        gettimeofday(&start, NULL);
    }

    if (call_num % 20 == 0) {
        printf("        Elapsed Value Interval\n");
    }
    gettimeofday(&cur, NULL);
    printf("%-7s %6.2f", msg, cur.tv_sec - start.tv_sec + (cur.tv_usec - start.tv_usec) / 1000000.0);

    if (include_timer) {
        struct itimerval itv;
        getitimer(ITIMER_REAL, &itv);
        printf("%6.2f %6.2f", itv.it_value.tv_sec + itv.it_value.tv_usec / 1000000.0,
                itv.it_interval.tv_sec + itv.it_interval.tv_usec / 1000000.0);
    }
    printf("\n");
    call_num++;
}

void SigalrmHandler(int sig) {
    got_alarm = 1;
}

int main() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = SigalrmHandler;
    sigaction(SIGALRM, &act, NULL);

    DisplayTimes("start:", 0);

    alarm(6);

    int sig_cnt = 0;
    clock_t prev_clock = clock();

    for (;;) {
        while (((clock() - prev_clock) * 10 / CLOCKS_PER_SEC) < 2) {
            if (got_alarm) {
                got_alarm = 0;
                DisplayTimes("alarm:", 1);
                printf("That's all folks\n");
                exit(0);
            }
        }
        prev_clock = clock();
        DisplayTimes("main:", 1);
    }
    return 0;
}
