// Copyright (c) 2018 The Didi Corporation and The Pickup Authors.
// All rights reserved. Use of this source code should be governed
// by the corporation. See the AUTHORS file for names of authors.
// Author: zhanglonghanks              Email: taihejin@whu.edu.cn
// Create: 2018-09-09 17:30:31 Last-Modified: 2018-09-09 17:30:31

#include <iostream>

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>

void Usage() {
    std::cout << "usage:\n  my_open_file <sockfd> <filename> <mode>" << std::endl;
}

int WriteFd(int fd, void* ptr, size_t nbytes, int sendfd);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Usage();
        return -1;
    }
    int fd = -1;
    if ((fd = open(argv[2], atoi(argv[3]))) < 0) {
        exit(errno > 0 ? errno : 255);
    }
    const char* ch = "c";
    std::cout << "write fd: " << fd << ", write char: " << ch << std::endl;
    if (WriteFd(atoi(argv[1]), (void*)ch, 1, fd) < 0) {
        exit(errno > 0 ? errno : 255);
    }
    return 0;
}

int WriteFd(int fd, void* ptr, size_t nbytes, int sendfd) {
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct msghdr msg;
    struct iovec iov[1];
    // build msg
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    
    struct cmsghdr* cmptr = CMSG_FIRSTHDR(&msg);
    cmptr->cmsg_len = CMSG_LEN(sizeof(int));
    cmptr->cmsg_level = SOL_SOCKET; 
    cmptr->cmsg_type = SCM_RIGHTS; 
    *((int *) CMSG_DATA(cmptr)) = sendfd;
    
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    // build iovec
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    return sendmsg(fd, &msg, 0);
}
