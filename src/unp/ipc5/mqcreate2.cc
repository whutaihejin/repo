#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <mqueue.h>
#include <stdlib.h> // for atol

#include <errno.h>
#include <string.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[]) {
    int c = 0;
    int flags = O_RDWR | O_CREAT;
    struct mq_attr attr;
    memset(&attr, 0, sizeof(struct mq_attr));
    while ((c = getopt(argc, argv, "em:z:")) != -1) {
        switch(c) {
            case 'e':
                flags |= O_EXCL;
                break;
            case 'm':
                attr.mq_maxmsg = atol(optarg);
                break;
            case 'z':
                attr.mq_msgsize = atol(optarg);
                break;

        }
    }
    if (optind != argc - 1) {
        // must be the last one
        printf("usage: %s [-e] [-m maxmsg -z massize] <mqname>\n", argv[0]);
        return 1;
    }
    
    //
    if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) ||
            (attr.mq_maxmsg == 0 && attr.mq_msgsize != 0)) {
        printf("must specify both -m maxmsg and -z msgsize\n");
        return 1;
    }
    //
    struct mq_attr* attr_ptr = (attr.mq_maxmsg != 0) ? &attr : NULL;
    mqd_t mqd = mq_open(argv[optind], flags, FILE_MODE, attr_ptr);
    if (mqd == -1) {
        printf("mqopen error: %s\n", strerror(errno));
        return 1;
    }
    return mq_close(mqd);
    // return 0;
}
