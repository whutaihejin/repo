#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void sigQuit(int signo) {
    printf("caught signo %s\n", strsignal(signo));
}

int main() {
    struct sigaction act, oact;
    sigset_t mask;
    sigemptyset(&mask);
    act.sa_mask = mask;
    act.sa_flags = 0;
#if defined(__APPLE__)
    printf("compile on mac os x platform\n");
    act.__sigaction_u.__sa_handler = sigQuit;
#elif defined(__linux__)
    printf("compile on linux platform\n");
    act.sa_handler = sigQuit;
#else
#error "unsuported platform"
#endif
    sigaction(SIGQUIT, &act, &oact);
    for (;;) {
        pause();
    }
    return 0;
}
