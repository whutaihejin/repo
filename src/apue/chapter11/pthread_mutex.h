#ifndef APUE_PTHREAD_MUTEX_H
#define APUE_PTHREAD_MUTEX_H

#include <pthread.h>

class Mutex;
class Condition;

class Mutex {
public:
    explicit Mutex() {
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
    //
    friend class Condition;

    pthread_mutex_t mutex_;

    // No copying allowed 
    Mutex(const Mutex&) = delete;
    void operator=(const Mutex&) = delete;
};

class LockGuard {
public:
    explicit LockGuard(Mutex* mutex): mutex_(mutex) {
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

class Condition {
public:
    explicit Condition(Mutex* mutex):mutex_(mutex) {
        pthread_cond_init(&cond_, nullptr);
    }

    void Wait() {
        pthread_cond_wait(&cond_, &(mutex_->mutex_));
    }

    void Signal() {
        pthread_cond_signal(&cond_);
    }

    void SignalAll() {
        pthread_cond_broadcast(&cond_);
    }

    ~Condition() {
        pthread_cond_destroy(&cond_);
    }

private:
    Mutex* mutex_;
    pthread_cond_t cond_;
};

#endif // APUE_PTHREAD_MUTEX_H
