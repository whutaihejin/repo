#include <unistd.h>
#include <iostream>

#include "event_loop.h"

void StartTask(EventLoop* loop) {
    loop->Loop();
}

int main() {
    std::cout << "this program will abort()" << std::endl;
    sleep(3);
    EventLoop loop;
    std::thread task(StartTask, &loop);
    
    loop.Loop();
    task.join();
    return 0;
}
