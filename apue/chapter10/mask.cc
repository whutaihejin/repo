#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include "mask.h"

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
