#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char* filename = ".lock.file";
    pid_t pid;
    if ((pid = fork()) == 0) {
        sleep(1);
        printf("child pid = %ld\n", (long)getpid());

        int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);

        for (int i = 0; i < 5; ++i) {
            struct flock flock;
            flock.l_type = F_WRLCK;
            flock.l_whence = SEEK_SET;
            flock.l_start = 0;
            flock.l_len = 0;
            int ret = fcntl(fd, F_GETLK, &flock);
            if (flock.l_type == F_UNLCK) {
                printf("child ret=%d no locked\n", ret);
            } else {
                printf("child ret=%d locked by pid=%lu\n", ret, (long)flock.l_pid);
            }
            sleep(1);
        }



        exit(0);
    }
    //
    printf("parent pid=%ld\n", (long)getpid());
    int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
    struct flock flock;
    flock.l_type = F_WRLCK;
    flock.l_whence = SEEK_SET;
    flock.l_start = 0;
    flock.l_len = 0;
    int ret = fcntl(fd, F_SETLK, &flock);
    printf("ret=%d\n", ret);
    //
    sleep(3);
    // close(fd);
    flock.l_type = F_UNLCK;
    ret = fcntl(fd, F_SETLK, &flock);
    printf("unlock ret=%d\n", ret);

    sleep(8);
    return 0;
}
