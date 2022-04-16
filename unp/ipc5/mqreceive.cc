#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <mqueue.h>

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <iostream>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[]) {
    int c = 0;
    int flags = O_RDWR;
    while ((c = getopt(argc, argv, "n")) != -1) {
        switch(c) {
            case 'n':
                flags |= O_NONBLOCK;
                break;
        }
    }
    if (optind != argc - 1) {
        // must be the last one
        printf("usage: %s [-n] <mqname>\n", argv[0]);
        return 1;
    }
    //
    mqd_t mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
    if (mqd == -1) {
        printf("mqopen error: %s\n", strerror(errno));
        return 1;
    }
    struct mq_attr attr;
    mq_getattr(mqd, &attr);

    char* buf = (char*)calloc((size_t)attr.mq_msgsize, sizeof(char));

    unsigned int priority = 0;
    int n = mq_receive(mqd, buf, attr.mq_msgsize, &priority);
    if (n != -1) {
        // display the message
        printf("rece: %ld bytes, priority: %u\n", (long)n, priority);
        printf("data: %s\n", buf);
    } else {
        printf("mqreceive error: %s\n", strerror(errno));
    }
    return 0;
}
