#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <pthread.h>

#include <string>

class FileLock {
public:
    FileLock(const std::string& template_name = "file_lock.XXXXXX") {
        // must copy caller's string in case it's a constant
        memcpy(template_name_, template_name.c_str(), template_name.size());
        file_descriptor_ = mkstemp(template_name_);

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
                printf("fcntl error in file lock: %s", strerror(errno));
            }
        }
    }

    void Unlock() {
        if (fcntl(file_descriptor_, F_SETLKW, &unlock_) < 0) {
            printf("fcntl error in file lock: %s", strerror(errno));
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
    printf("thread %ld lock file\n", pthread_self());
    fflush(NULL);
    sleep(3);
    lock->Unlock();
    return NULL;
}

int main() {
    FileLock lock;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, WriteFile, &lock);
    pthread_create(&tid2, NULL, WriteFile, &lock);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
