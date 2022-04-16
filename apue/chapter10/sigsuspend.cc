#include <stdio.h>
#include <signal.h>

#include "mask.h"

void sigInterrupt(int signo);

int main() {
    sigset_t new_mask, old_mask, wait_mask;
    mask("program start:");

    signal(SIGINT, sigInterrupt);

    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGUSR1);

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

    // block SIGINT and save current signal mask
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    // critical region of code
    mask("in critical region:");


    // pause, allowing all signals except SIGUSR1
    sigsuspend(&wait_mask);

    mask("after return from sigsuspend");

    sigprocmask(SIG_SETMASK, &old_mask, nullptr);

    mask("program exit:");

    return 0;
}

void sigInterrupt(int signo) {
    mask("\nin sig interrupt:");
}
