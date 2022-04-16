#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <mqueue.h>

#include <errno.h>
#include <string.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[]) {
    int flags = O_RDWR | O_CREAT;
    int c = 0;
    while ((c = getopt(argc, argv, "e")) != -1) {
        switch(c) {
            case 'e':
                flags |= O_EXCL;
                break;
        }
    }
    if (optind != argc - 1) {
        // must be the last one
        printf("usage: %s [-e] <mqname>\n", argv[0]);
        return 1;
    }
    //
    mqd_t mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
    if (mqd == -1) {
        printf("mqopen error: %s\n", strerror(errno));
        return 1;
    }
    struct mq_attr attr;
    if (mq_getattr(mqd, &attr) != 0) {
        printf("mq_getattr error: %s\n", strerror(errno));
        return 1;
    }
    printf("flag: %ld, maxmsg: %ld, msgsize: %ld, curmsgs: %ld\n", 
            attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    return mq_close(mqd);
    // return 0;
}
