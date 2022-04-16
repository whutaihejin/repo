// Copyright (c) 2018 The Didi Corporation and The Pickup Authors.
// All rights reserved. Use of this source code should be governed
// by the corporation. See the AUTHORS file for names of authors.
// Author: zhanglonghanks              Email: taihejin@whu.edu.cn
// Create: 2018-09-19 23:44:28 Last-Modified: 2018-09-19 23:44:28

#include <stdio.h>
#include <mqueue.h>

#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: %s <mqname>\n", argv[0]);
        return 1;
    }
    int code = mq_unlink(argv[1]);
    if (code != 0) {
        printf("mq_unlink error: %s\n", strerror(errno));
        return 1;
    }
}
