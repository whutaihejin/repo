#include <stdio.h>
#include <pthread.h>

#include "pthread_mutex.h"

int main() {
    Mutex mutex;
    mutex.Lock();
    mutex.Lock();
    return 0;
}
