#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigQuit(int);

int main() {
    sigset_t new_mask;
    sigset_t old_mask;
    sigset_t pend_mask;

    if (signal(SIGQUIT, sigQuit) == SIG_ERR) {
        printf("can't catch SIGQUIT\n");
        exit(0);
    }

    // Block SIGQUIT and save current signal mask
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        printf("sigprocmask error\n");
        exit(0);
    }

    sleep(5);
    if (sigpending(&pend_mask) < 0) {
        printf("sigpending error\n");
        exit(0);
    }
    if (sigismember(&pend_mask, SIGQUIT)) {
        printf("\nSIGQUIT penging\n");
    }

    // restore signal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &old_mask, nullptr) < 0) {
        printf("sigprocmask 2 error\n");
        exit(0);
    }
    printf("SIGQUIT unblocked\n");

    sleep(10);
    return 0;
}

void sigQuit(int signo) {
    printf("caught SIGQUIT\n");
    fflush(nullptr);
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        printf("can't reset SIGQUIT\n");
        exit(0);
    }
}
