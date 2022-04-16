#include <stdio.h>
#include <stdlib.h>

#include "apue.h"

static void clear();
static void write();

int main() {
    if (atexit(clear) != 0) {
        err_sys("can't register clear");
    }
    if (atexit(write) != 0) {
        err_sys("can't register write");
    }
    if (atexit(write) != 0) {
        err_sys("can't register write");
    }
    printf("I am exiting\n");
    exit(0);
}

static void clear() {
    printf("I am clear ing...\n");
}

static void write() {
    printf("I am write ing...\n");
}
