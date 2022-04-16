#include <stdio.h>
#include <signal.h>
#include <assert.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigfillset(&set);
    sigdelset(&set, SIGINT);
    sigaddset(&set, SIGINT);
    assert(sigismember(&set, SIGINT));
    return 0;
}
