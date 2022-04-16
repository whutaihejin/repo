#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

inline int FileLock(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;
    return fcntl(fd, cmd, &lock);
}

// file read lock
inline int ReadLock(int fd, off_t offset, int whence, off_t len) {
    return FileLock(fd, F_SETLK, F_RDLCK, offset, whence, len);
}

inline int ReadwLock(int fd, off_t offset, int whence, off_t len) {
    return FileLock(fd, F_SETLKW, F_RDLCK, offset, whence, len);
}

inline int WriteLock(int fd, off_t offset, int whence, off_t len) {
    return FileLock(fd, F_SETLK, F_WRLCK, offset, whence, len);
}

inline int WritewLock(int fd, off_t offset, int whence, off_t len) {
    return FileLock(fd, F_SETLKW, F_WRLCK, offset, whence, len);
}

inline int FileUnlock(int fd, off_t offset, int whence, off_t len) {
    return FileLock(fd, F_SETLKW, F_UNLCK, offset, whence, len);
}

inline pid_t FileInLock(int fd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;
    fcntl(fd, F_GETLK, &lock);
    return lock.l_type == F_UNLCK ? 0 : lock.l_pid;
}

int main() {
    const char* filename = ".lock_test.dat";
    int fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
    
    // writeLock(fd);
    pid_t pid;
    if ((pid = fork()) == 0) {
        // child
        sleep(1);
        printf("child start pid = %lu\n", (long)getpid());
        fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
        for (size_t i = 0; i < 5; ++i) {
            printf("lock pid: %lu\n", (long)FileInLock(fd, F_WRLCK, 0, SEEK_SET, 0));
            sleep(1);
        }
        unlink(filename);
        exit(0);
    } else {
        // parent
        printf("parent sleep pid = %lu\n", (long)getpid());
        WritewLock(fd, 0, SEEK_SET, 0);
        sleep(2);
        // FileUnlock(fd, 0, SEEK_SET, 0);
        close(fd);
        sleep(5);
    }
    unlink(filename);
    return 0;
}
