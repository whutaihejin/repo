#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int LockFile(int fd, int cmd, int type, int whence, off_t offset, off_t len) {
    struct flock l;
    l.l_type = type;
    l.l_whence = whence;
    l.l_start = offset;
    l.l_len = len;
    return fcntl(fd, cmd, &l);
}

int ReadLockFile(int fd, int whence, off_t offset, off_t len) {
    return LockFile(fd, F_SETLK, F_RDLCK, whence, offset, len);
}

int ReadwLockFile(int fd, int whence, off_t offset, off_t len) {
    return LockFile(fd, F_SETLKW, F_RDLCK, whence, offset, len);
}

int WriteLockFile(int fd, int whence, off_t offset, off_t len) {
    return LockFile(fd, F_SETLK, F_WRLCK, whence, offset, len);
}

int WritewLockFile(int fd, int whence, off_t offset, off_t len) {
    return LockFile(fd, F_SETLKW, F_WRLCK, whence, offset, len);
}

int UnlockFile(int fd, int whence, off_t offset, off_t len) {
    return LockFile(fd, F_SETLKW, F_UNLCK, whence, offset, len);
}

int TestFileLock(int fd, int type, int whence, off_t offset, off_t len) {
    struct flock l;
    l.l_type = type;
    l.l_whence = whence;
    l.l_start = offset;
    l.l_len = len;
    if (fcntl(fd, F_GETLK, &l) != 0) {
        return -1;
    }
    return (l.l_type == F_UNLCK) ? 0 : l.l_pid;
}

int main() {
    const char* filename = ".lock.file";
    pid_t pid;
    if ((pid = fork()) == 0) {
        sleep(1);
        printf("child pid = %ld\n", (long)getpid());
        int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);

        for (int i = 0; i < 6; ++i) {
            int ret = TestFileLock(fd, F_WRLCK, SEEK_SET, 0, 0);
            printf("child locked by pid=%d\n", ret);
            sleep(1);
        }

        exit(0);
    }
    //
    printf("parent pid=%ld\n", (long)getpid());
    int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
    int ret = WriteLockFile(fd, SEEK_SET, 0, 0);
    printf("parent lock file ret=%d\n", ret);
    //
    sleep(3);
    close(fd);
    // ret = UnlockFile(fd, SEEK_SET, 0, 0);
    printf("parent unlock file ret=%d\n", 0);

    sleep(8);
    unlink(filename);
    return 0;
}
