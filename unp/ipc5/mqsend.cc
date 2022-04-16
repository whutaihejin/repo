#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <mqueue.h>

#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <iostream>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

struct Option {
    Option(): size(0), priority(1) {}
    size_t size;
    size_t priority;

    friend std::ostream& operator<<(std::ostream&, const Option&);
};

int main(int argc, char* argv[]) {
    int c = 0;
    int flags = O_RDWR | O_CREAT;
    struct Option option;
    while ((c = getopt(argc, argv, "es:p:")) != -1) {
        switch(c) {
            case 'e':
                flags |= O_EXCL;
                break;
            case 's':
               option.size = atol(optarg);
               break;
            case 'p':
               option.priority = atol(optarg);
               break;
        }
    }
    if (optind != argc - 1) {
        // must be the last one
        printf("usage: %s [-e] [-s maxsize] [-p priority] <mqname>\n", argv[0]);
        return 1;
    }
    //
    mqd_t mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
    if (mqd == -1) {
        printf("mqopen error: %s\n", strerror(errno));
        return 1;
    }
    char* ptr = (char*)calloc(option.size, sizeof(char));
    memset(ptr, 'a', option.size);
    if (mq_send(mqd, ptr, option.size, option.priority) != 0) {
        printf("mqsend error: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
