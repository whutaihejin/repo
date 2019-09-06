#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

pid_t TestLock(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    if (fcntl(fd, F_SETLK, &lock) != 0) {
        return 0;
    }
    return lock.l_pid;
}

int main() {
    int fd = open(".lock_test.dat", O_RDWR | O_CREAT);
    // writeLock(fd);
    pid_t pid;
    if ((pid = fork()) == 0) {
        // child
        printf("child start...\n");
        exit(0);
    } else {
        // parent
        printf("parent sleep\n");
        sleep(2);
    }
    return 0;
}
