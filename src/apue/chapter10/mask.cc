#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void mask(const char* str);

int main() {
    sigset_t set, oset;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &set, &oset);
    mask("show sinal mask");
    sigprocmask(SIG_SETMASK, &oset, nullptr);
    mask("origin mask");
    return 0;
}

#define sigout(set, sig) if (sigismember(&set, sig)) { printf(fmt, strsignal(sig)); }

void mask(const char* str) {
    sigset_t set;
    int errno_save;

    errno_save = errno;
    const char* fmt = " [%s],";
    if (sigprocmask(0, nullptr, &set) == 0) {
        printf("%s: ", str);
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
