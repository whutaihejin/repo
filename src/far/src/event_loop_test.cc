#include <iostream>

#include "event_loop.h"

void StartTask() {
    EventLoop loop;
    loop.Loop();
}

int main() {
    EventLoop loop;
    std::thread task(StartTask);
    
    loop.Loop();
    task.join();
    return 0;
}
