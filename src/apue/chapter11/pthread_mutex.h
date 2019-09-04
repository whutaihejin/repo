#ifndef APUE_PTHREAD_MUTEX_H
#define APUE_PTHREAD_MUTEX_H

#include <pthread.h>

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&mutex_, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    void Lock() {
        pthread_mutex_lock(&mutex_);
    }

    void Unlock() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
   
    // No copying allowed 
    Mutex(const Mutex&) = delete;
    void operator=(const Mutex&) = delete;
};

class LockGuard {
public:
    LockGuard(Mutex* mutex): mutex_(mutex) {
        mutex_->Lock();
    }

    ~LockGuard() {
        mutex_->Unlock();
    }
private:
    Mutex* mutex_;

    // No copying allowed
    LockGuard(const LockGuard&) = delete;
    void operator=(const LockGuard&) = delete;
};

#endif // APUE_PTHREAD_MUTEX_H
