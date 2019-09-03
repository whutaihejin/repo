#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void sigUsr1(int signo);
void sigAlrm(int signo);
void mask(const char* str);

sigjmp_buf jmpbuf;
volatile sig_atomic_t canjmp;

int main() {
    signal(SIGUSR1, sigUsr1);
    signal(SIGALRM, sigAlrm);
    mask("start main:");

    if (sigsetjmp(jmpbuf, 1)) {
        mask("ending main:");
        return 1;
    }
    canjmp = 1;
    for (;;) {
        pause();
    }
    return 0;
}

void sigUsr1(int signo) {
    time_t start;
    if (canjmp == 0) {
        return;
    }
    mask("start sig usr1");
    alarm(3);
    start = time(nullptr);
    for (;;) {
        if (time(nullptr) > start + 5) {
            break;
        }
    }
    mask("finishing sig usr1");
    canjmp = 0;
    siglongjmp(jmpbuf,  1);
}

void sigAlrm(int signo) {
    mask("in sig alrm");
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
