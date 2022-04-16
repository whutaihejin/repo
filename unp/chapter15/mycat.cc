// Copyright (c) 2018 The Didi Corporation and The Pickup Authors.
// All rights reserved. Use of this source code should be governed
// by the corporation. See the AUTHORS file for names of authors.
// Author: zhanglonghanks              Email: taihejin@whu.edu.cn
// Create: 2018-09-09 16:28:52 Last-Modified: 2018-09-09 16:28:52

#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFSIZE 1024

#define ERROR_LOG(prefix, code) \
    do { std::cout << prefix << " code=" << code << " msg=" << strerror(code) << std::endl; } while(0)

void Usage() {
    std::cout << "usage:\n  mycat <pathname>" << std::endl;
}

int MyOpen(const char*, int);
int ReadFd(int fd, void* ptr, size_t nbytes, int* recvfd);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        Usage();
        return -1;
    }
    char buf[BUFSIZE];
    int fd = 0;
    if ((fd = MyOpen(argv[1], O_RDONLY)) < 0) {
        std::cout << "cannot open " << argv[1] << std::endl;
        return -1;
    }
    int n = 0; // for count
    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    return 0;
}

int MyOpen(const char* pathname, int mode) {
    int sockfd[2];
    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd) == -1) {
        ERROR_LOG("sockpair error", errno);
        return -1;
    }
    
    // fork child process
    pid_t pid = 0;
    if ((pid = fork()) == 0) { // child process
        close(sockfd[0]);
        char arg_sockfd[10] = {0};
        char arg_mode[10] = {10};
        snprintf(arg_sockfd, sizeof(arg_sockfd), "%d", sockfd[1]);
        snprintf(arg_mode, sizeof(arg_mode), "%d", mode);
        execl("openfile", "openfile", arg_sockfd, pathname, arg_mode, (char*)NULL);
        // Should not reach here unless encounter an error.
        ERROR_LOG("execl error", errno);
        exit(errno);
    }
    
    // parent process: wait for the child to terminate
    close(sockfd[1]);
    int fd = -1, status = -1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) == 0) {
        ERROR_LOG("child did not terminate", 0);
        exit(-1);
    }
    if ((status = WEXITSTATUS(status)) == 0) {
        char ch = 'a';
        ReadFd(sockfd[0], &ch, 1, &fd);
        std::cout << "read fd: " << fd << ", read char: " << ch << std::endl;
    } else {
        errno = status;
        fd = -1;
    }
    close(sockfd[0]);
    return fd; 
}

int ReadFd(int fd, void* ptr, size_t nbytes, int* recvfd) {
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct msghdr msg;
    struct iovec iov[1];
    // build msg
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    // build iovec
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    // read msg
    int n = 0; // for count
    if ((n = recvmsg(fd, &msg, 0)) <= 0) {
        return n;
    }
    struct cmsghdr* cmptr = NULL;
    if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL && cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmptr->cmsg_level != SOL_SOCKET) {
            ERROR_LOG("control level not equal SOL_SOCKET", 0);
        }
        if (cmptr->cmsg_type != SCM_RIGHTS) {
            ERROR_LOG("control type not equal SCM_RIGHTS", 0);
        }
        *recvfd = *((int *) CMSG_DATA(cmptr));
    } else {
        *recvfd = -1;
    }
    return n;
}
