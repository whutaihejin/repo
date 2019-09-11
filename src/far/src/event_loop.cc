#include <cstdlib>
#include <iostream>
#include <poll.h>

#include "poller.h"
#include "channel.h"
#include "event_loop.h"

__thread EventLoop* LOOP_IN_THIS_THREAD = 0;

EventLoop::EventLoop():
    quit_(false),
    is_loop_(false),
    thread_id_(std::this_thread::get_id()),
    poller_(std::make_shared<Poller>(this)) {
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
    quit_ = false;

    while (quit_) {
        this->active_channels_.clear();
        poller_->Poll(kPollTimeout, &active_channels_);
        for (auto it = active_channels_.begin(); it != active_channels_.end(); ++it) {
            (*it)->HandleEvent();
        }
    }
    std::cout << "EventLoop " << this << " stop looping" << std::endl;
    is_loop_ = false;
}

void EventLoop::Quit() {
    this->quit_ = true;
}

void EventLoop::UpdateChannel(Channel* channel) {
    assert(channel->OwnerLoop() == this);
    AssertInLoopThread();
    this->poller_->UpdateChannel(channel);
}
