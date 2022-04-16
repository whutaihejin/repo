#include <iostream>
#include <thread>
#include <mutex>

class Data {
public:
    Data(): val_(0), name_() {}
    void Process() {
        std::cout << "Process() " << val_  << " " << name_ << std::endl;
    }
private:
    int val_;
    std::string name_;
};

class Wrapper {
public:
    template<typename T> void ProcessData(T func) {
        std::lock_guard<std::mutex> guard(mutex_);
        func(data_);
    }
private:
    Data data_;
    std::mutex mutex_;
};

Data* unprotected;
void MaliciousFunction(Data& data) {
    unprotected = &data;
}

// Don't pass pointers and references to protected data outside the scope
// of the lock, whether by returning them from a function, storing them
// in externally visible memory, or passing them as arguments to user-supplied functions.
int main() {
    Wrapper wrapper;
    wrapper.ProcessData(MaliciousFunction);
    unprotected->Process();
    return 0;
}
