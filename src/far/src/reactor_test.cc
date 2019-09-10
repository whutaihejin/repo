#include <iostream>
#include <sys/timerfd.h>

#include "poller.h"
#include "channel.h"
#include "event_loop.h"


void Timeout(EventLoop* l) {
    std::cout << "timeout!" << std::endl;
    l->Quit();
}

int main() {
    EventLoop loop;
    int timerfd = timerfd_create();
    return 0;
}
