#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/mman.h>
#include <sys/wait.h>

class ProcessLock {
public:
    ProcessLock(): fd_(-1), mutex_(NULL) {
        const char* pathname = "mmap_lock";
        if ((fd_ = open(pathname, O_RDWR | O_CREAT, 0644)) == -1) {
            printf("open error: %s\n", strerror(errno));
            fd_ = -1;
            return;
        }
        // truncate shared memory segment so it would contain pthread_mutex_t.
        if (ftruncate(fd_, sizeof(pthread_mutex_t)) != 0) {
            printf("ftruncate error: %s\n", strerror(errno));
            fd_ = -1;
            return;
        }
        mutex_ = (pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (mutex_ == MAP_FAILED) {
            printf("mmap error: %s\n", strerror(errno));
            mutex_ = NULL;
            return;
        }
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED) != 0) {
            printf("setpshared error: %s\n", strerror(errno));
            return;
        }
        pthread_mutex_init(mutex_, &attr);
        //
        unlink(pathname);
        close(fd_);
    }

    void Lock() {
        if (mutex_ != NULL) {
            pthread_mutex_lock(mutex_);
        }
    }

    void Unlock() {
        if (mutex_ != NULL) {
            pthread_mutex_unlock(mutex_);
        }
    }

private:
    int fd_;
    pthread_mutex_t* mutex_;
    pthread_mutex_t m_;
};

void* WriteFile(void *arg) {
    ProcessLock* lock = static_cast<ProcessLock*>(arg);
    lock->Lock();
    printf("process %ld lock file\n", getpid());
    fflush(NULL);
    sleep(3);
    lock->Unlock();
    return NULL;
}

int main() {
    ProcessLock lock;
    printf("main process %ld\n", getpid());
    pid_t pid;
    if ((pid = fork()) == 0) {
        // child processs
        WriteFile(&lock);
        exit(0);
    }
    WriteFile(&lock);
    wait(NULL);
    return 0;
}
