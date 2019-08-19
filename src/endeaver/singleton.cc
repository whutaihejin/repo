#include <iostream>
#include <pthread.h>

// class Singleton {
// public:
//     static Singleton* Instance() {
//         static Singleton instance;
//         return &instance;
//     }
// 
//     int getStatus() {
//         return status;
//     }
// 
// private:
//     Singleton(): status(0) {
//         std::cout << "construct singleton instance..." << std::endl;
//     }
//     int status;
// };
//
class Singleton {
public:
    static Singleton* Instance() {
        if (instance_ == NULL) {
            pthread_mutex_lock(&mutex_);
            if (instance_ == NULL) {
                instance_ = new Singleton();
            }
            pthread_mutex_unlock(&mutex_);
        }
        return instance_;
    }

    int getStatus() {
        return status;
    }

    void Incr() {
        status++;
    }

private:
    Singleton() {
        std::cout << "construct singleton instance..." << std::endl;
    }
    static Singleton* instance_;
    static pthread_mutex_t mutex_;
    int status;
};

Singleton* Singleton::instance_ = NULL;
pthread_mutex_t Singleton::mutex_ = PTHREAD_MUTEX_INITIALIZER;

int main() {
    Singleton* s = Singleton::Instance();
    s->Incr();
    std::cout << "status: " << s->getStatus() << std::endl;
    s->Incr();
    std::cout << "status: " << s->getStatus() << std::endl;
}
