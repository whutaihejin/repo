#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "poller.h"
#include "channel.h"
#include "event_loop.h"


void Timeout(EventLoop* l) {
    std::cout << "timeout!" << std::endl;
    l->Quit();
}

void StartTask(int fd) {
    sleep(2);
    write(fd, "a", 1);
}

int main() {
    EventLoop loop;
    int fd[2];
    pipe(fd);
    
    Channel channel(&loop, fd[0]);
    channel.setReadCallback(std::bind(Timeout, &loop));
    channel.EnableRead();

    // std::thread writer(StartTask, fd[1]);

    loop.Loop();
    // writer.join();
    return 0;
}
