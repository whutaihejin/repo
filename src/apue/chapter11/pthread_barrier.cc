#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <climits>
#include <vector>
#include <algorithm>

const size_t kThreads = 8;
const size_t kTotalSize = 800;
const size_t kSpan = kTotalSize / kThreads;

size_t nums[kTotalSize];
size_t copy[kTotalSize];

pthread_barrier_t barrier;

void* PartitionSort(void* arg) {
    size_t start = (size_t)arg;
    size_t* ptr = &nums[start];
    std::sort(ptr, ptr + kSpan);
    pthread_barrier_wait(&barrier);
    return (void*)0;
}

void merge() {
    size_t k = 0;
    std::vector<size_t> forward;
    for (size_t i = 0; i < kThreads; ++i) {
        forward.push_back(i * kSpan);
    }
    for (size_t i = 0; i < kTotalSize; ++i) {
        size_t min_val = INT_MAX, min_idx = 0;
        for (size_t i = 0; i < kThreads; ++i) {
            if (forward[i] < (i + 1) * kSpan && nums[forward[i]] < min_val) {
                min_val = nums[forward[i]];
                min_idx = i;
            }
        }
        copy[k++] = min_val;
        forward[min_idx]++;
    }
}

int main(int argc, char* argv[]) {
    pthread_barrier_init(&barrier, nullptr, kThreads + 1);
    for (size_t i = 0; i < kTotalSize; ++i) {
        nums[i] = rand() % 10000;
    }
    if (argc >= 2) {
        std::vector<pthread_t> tid_vec(kThreads);
        for (size_t i = 0; i < kThreads; ++i) {
            pthread_create(&tid_vec[i], nullptr, PartitionSort, (void*)(i * kSpan));
        }
        pthread_barrier_wait(&barrier);
        merge();
        for (size_t i = 0; i < kTotalSize; ++i) {
            printf("->%lu ", copy[i]);
            if ((i + 1) % 10 == 0) printf("\n");
        }
        for (size_t i = 0; i < kThreads; ++i) {
            pthread_join(tid_vec[i], nullptr);
        }
    } else {
        std::sort(std::begin(nums), std::end(nums));
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}
