#include <cstdlib>
#include <iostream>
#include <poll.h>

#include "event_loop.h"

__thread EventLoop* LOOP_IN_THIS_THREAD = 0;

EventLoop::EventLoop(): is_loop_(false), thread_id_(std::this_thread::get_id()) {
    std::cout << "EventLoop created " << this << " in thread " << this->thread_id_ << std::endl;
}

EventLoop::~EventLoop() {
    assert(!is_loop_);
    LOOP_IN_THIS_THREAD = nullptr;
}

void EventLoop::Loop() {
    assert(!is_loop_);
    this->AssertInLoopThread();
    is_loop_ = true;

    poll(nullptr, 0, 5 * 1000); // five seconds

    std::cout << "EventLoop " << this << " stop looping" << std::endl;

    is_loop_ = false;
}
