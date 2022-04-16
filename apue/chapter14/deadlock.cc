#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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
    const char* filename = "deadlock.lock";
    int fd;
    if ((fd = open(filename, O_RDWR|O_CREAT, S_IRWXU)) < 0) {
        fprintf(stderr, "open error\n"), exit(1);
    }
    if (write(fd, "ab", 2) != 2) {
        fprintf(stderr, "write error\n"), exit(1);
    }

    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n"), exit(1);
    } else if (pid == 0) {
        // child
        sleep(1);
        if (WriteLockFile(fd, SEEK_SET, 0, 1) != 0) {
            printf("child pid %ld error %s\n", (long)getpid(), strerror(errno));
        }
        sleep(1);
        if (WriteLockFile(fd, SEEK_SET, 1, 1) != 0) {
            printf("child pid %ld error %s\n", (long)getpid(), strerror(errno));
        }
    } else {
        // parent
        if (WriteLockFile(fd, SEEK_SET, 1, 1) != 0) {
            printf("parent pid %ld error %s\n", (long)getpid(), strerror(errno));
        }
        sleep(3);
        if (WriteLockFile(fd, SEEK_SET, 0, 1) != 0) {
            printf("parent pid %ld error %s\n", (long)getpid(), strerror(errno));
        }
        sleep(5);
    }
    unlink(filename);
    return 0;
}
