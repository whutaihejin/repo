#include <iostream>
#include <poll.h>
#include <cassert>

#include "poller.h"
#include "channel.h"
#include "event_loop.h"

Poller::Poller(EventLoop* eloop): eloop_(eloop) {}

Poller::~Poller() {}

int64_t Poller::Poll(int timeout, ChannelList* active_channels) {
    int num = poll((struct pollfd*)pollfds_.data(), pollfds_.size(), timeout);
    time_t now = time(nullptr);
    if (num > 0) {
        std::cout << num << " events happended" << std::endl;
        FillActiveChannels(num, active_channels);
    } else if (num == 0) {
        std::cout << "poll detect nothing hanppended!" << std::endl;
    } else {
        std::cerr << "poll error" << std::endl;
    }
    return now;
}

void Poller::FillActiveChannels(int num, ChannelList* active_channels) const {
    for (auto it = pollfds_.begin(); it != pollfds_.end() && num > 0; ++it) {
        if (it->revents > 0) {
            --num;
            auto c = this->channel_map_.find(it->fd);
            assert(c != channel_map_.end());
            Channel* channel = c->second;
            assert(channel->fd() == it->fd);
            channel->setRevents(it->revents);
            active_channels->push_back(channel);
        }
    }
}

void Poller::UpdateChannel(Channel* channel) {
    this->AssertInLoopThread();
    std::cout << channel->EventsToString() << std::endl;
    if (channel->index() < 0) {
        // a new one, add to pollfds_
        assert(channel_map_.find(channel->fd()) == channel_map_.end());
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = channel->events();
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        // store index into channel
        channel->setIndex(pollfds_.size() - 1);
        // build fd to channel
        channel_map_[pfd.fd] = channel;
    } else {
        // update existing one
        assert(channel_map_.find(channel->fd()) != channel_map_.end());
        assert(channel_map_[channel->fd()] = channel);
        size_t index = channel->index();
        assert(0u <= index && index < pollfds_.size());
        struct pollfd& pfd = pollfds_[index];
        assert(pfd.fd == channel->fd() || pfd.fd == -1);
        pfd.events = channel->events();
        pfd.revents = 0;
        if (channel->IsNoneEvent()) {
            pfd.fd = -1; // ignore this pollfd
        }
    }
}

void Poller::AssertInLoopThread() {
    this->eloop_->AssertInLoopThread();
}
