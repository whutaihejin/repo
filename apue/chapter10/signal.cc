#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void userSignalCatch(int signo) {
    switch (signo) {
        case SIGUSR1:
            printf("received SIGUSR1\n");
            break;
        case SIGUSR2:
            printf("received SIGUSR2\n");
            break;
        default:
            printf("received signal with %d\n", signo);
            break;
    }
}

int main() {
    if (signal(SIGUSR1, userSignalCatch) == SIG_ERR) {
        printf("signal error\n");
        exit(-1);
    }    
    if (signal(SIGUSR2, userSignalCatch) == SIG_ERR) {
        printf("signal error\n");
        exit(-1);
    }
    for (;;) {
        pause();
    }
    return 0;
}
