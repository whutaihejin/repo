#include <stdio.h>
#include <signal.h>
#include <string.h>

// global variable
volatile sig_atomic_t quit_flag = 0;

void sigInterrupt(int signo);

int main() {
    sigset_t new_mask, old_mask, zero_mask;

    signal(SIGINT, sigInterrupt);
    signal(SIGQUIT, sigInterrupt);

    sigemptyset(&zero_mask);

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGQUIT);

    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    while (quit_flag == 0) {
        sigsuspend(&zero_mask);
    }

    quit_flag = 0;

    sigprocmask(SIG_SETMASK, &old_mask, nullptr);
    return 0;
}

void sigInterrupt(int signo) {
    if (signo == SIGQUIT) {
        quit_flag = 1;
    } else if (signo == SIGINT) {
        printf("\ninterrupt\n");
    } else {
        printf("unknown signal %s\n", strsignal(signo));
    }
}
