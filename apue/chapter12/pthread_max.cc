#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <vector>

void* StartTask(void* arg) {
    for (;;) {
        sleep(1);
    }
    return nullptr;
}

int main() {
    std::vector<pthread_t> vec;
    for (size_t i = 0;; ++i) {
        vec.push_back(0);
        pthread_create(&vec.back(), nullptr, StartTask, nullptr);
        printf("->%lu ", i);
        if ((i + 1) % 50 == 0) printf("\n");
    }
    return 0;
}
