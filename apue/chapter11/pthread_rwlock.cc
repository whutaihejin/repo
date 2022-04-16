#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

struct Job {
    Job(): id(0), prev(nullptr), next(nullptr) {}
    size_t id;
    struct Job* prev;
    struct Job* next;
};

class Queue {
public:
    explicit Queue(): tail_(&head_) {
            head_.next = head_.prev = nullptr;
            pthread_rwlock_init(&rwlock_, nullptr);
    }

    ~Queue() {
        pthread_rwlock_destroy(&rwlock_);
    }

    int Insert(Job* job) {
        pthread_rwlock_wrlock(&rwlock_);
        job->next = head_.next;
        if (head_.next) {
            head_.next->prev = job;
        } else {
            tail_ = job; // empty
        }
        job->prev = &head_;
        head_.next = job;
        pthread_rwlock_unlock(&rwlock_);
        return 0;
    }

    int Append(Job* job) {
        pthread_rwlock_wrlock(&rwlock_);
        job->next = nullptr;
        job->prev = tail_;
        tail_->next = job;
        // reset tail
        tail_ = job;
        pthread_rwlock_unlock(&rwlock_);
        return 0;
    }

    void Remove(Job *job) {
        pthread_rwlock_wrlock(&rwlock_);
        job->prev->next = job->next;
        if (job->next) {
            job->next->prev = job->prev;
        } else {
            tail_ = job->prev;
        }
        pthread_rwlock_unlock(&rwlock_);
    }

    Job *Find(size_t id) {
        struct Job* p = nullptr;
        pthread_rwlock_rdlock(&rwlock_);
        for (p = head_.next; p != nullptr; p = p->next) {
            if (p->id == id) {
                break;
            }
        }
        pthread_rwlock_unlock(&rwlock_);
        return p;
    }

    Job *List() {
        struct Job* p = nullptr;
        pthread_rwlock_rdlock(&rwlock_);
        for (p = head_.next; p != nullptr; p = p->next) {
            printf("->%lu ", p->id);
        }
        printf("\n");
        // for (p = tail_; p != &head_; p = p->prev) {
        //     printf("->%lu ", p->id);
        // }
        // printf("\n");
        pthread_rwlock_unlock(&rwlock_);
        return p;
    }


private:
    Job head_;
    Job* tail_;
    pthread_rwlock_t rwlock_;
};

int main() {
    Queue queue;
    size_t limit = 19;
    for (int i = 0; i < limit; ++i) {
        Job* job = (Job*)malloc(sizeof(struct Job));
        job->id = i;
        if (rand() & 0x01) {
            queue.Insert(job);
        } else {
            queue.Append(job);
        }
    }

   
    queue.List();

    // find and remove
    for (int i = 0; i < limit; ++i) {
        Job* job = queue.Find(i);
        assert(job != nullptr);
        queue.Remove(job);
        printf("->%lu ", job->id);
        free(job);
    }
    printf("\n");
    return 0;
}
