#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#ifndef APUE_MASK_H
#define APUE_MASK_H

#define sigout(set, sig) if (sigismember(&set, sig)) { printf(fmt, strsignal(sig)); }

void mask(const char* str) {
    sigset_t set;
    int errno_save;

    errno_save = errno;
    const char* fmt = " [%s],";
    if (sigprocmask(0, nullptr, &set) == 0) {
        printf("%s ", str);
        sigout(set, SIGINT);
        sigout(set, SIGQUIT);
        sigout(set, SIGHUP);
        sigout(set, SIGALRM);
        sigout(set, SIGTERM);
        sigout(set, SIGSTOP);
        sigout(set, SIGTSTP);
        sigout(set, SIGCONT);
        sigout(set, SIGCHLD);
        sigout(set, SIGTTIN);
        sigout(set, SIGTTOU);
        sigout(set, SIGUSR1);
        sigout(set, SIGUSR2);
        printf("\n");
    }
    errno = errno_save;
}

#endif // APUE_MASK_H
