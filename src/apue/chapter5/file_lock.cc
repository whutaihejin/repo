#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/wait.h>

#include <pthread.h>

#include <string>

class FileLock {
public:
    FileLock(const std::string& template_name = "file_lock.XXXXXX") {
        // must copy caller's string in case it's a constant
        memset(template_name_, 0, sizeof(template_name_));
        memcpy(template_name_, template_name.c_str(), template_name.size());
        if ((file_descriptor_ = mkstemp(template_name_)) == -1) {
            printf("mkstemp error in file lock: %s\n", strerror(errno));
        }

        //
        lock_.l_type = F_WRLCK;
        lock_.l_whence = SEEK_SET;
        lock_.l_start = 0;
        lock_.l_len = 0;
       
        //
        unlock_.l_type = F_UNLCK;
        unlock_.l_whence = SEEK_SET;
        unlock_.l_start = 0;
        unlock_.l_len = 0;
    }

    void Lock() {
        int rc = 0;
        while ((rc = fcntl(file_descriptor_, F_SETLKW, &lock_)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                printf("fcntl error in file lock: %s\n", strerror(errno));
                break;
            }
        }
    }

    void Unlock() {
        if (fcntl(file_descriptor_, F_SETLKW, &unlock_) < 0) {
            printf("fcntl error in file lock: %s\n", strerror(errno));
        }
    }
   
    ~FileLock() {
        unlink(template_name_);
        close(file_descriptor_);
    }

private:
    char template_name_[1024];
    int file_descriptor_;
    struct flock lock_;
    struct flock unlock_;
};

void* WriteFile(void *arg) {
    FileLock* lock = static_cast<FileLock*>(arg);
    lock->Lock();
    printf("process %ld lock file\n", getpid());
    fflush(NULL);
    sleep(3);
    lock->Unlock();
    return NULL;
}

int main() {
    FileLock lock;
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
