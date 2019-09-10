#include <iostream>
#include <sstream>

#include "channel.h"
#include "event_loop.h"

Channel::Channel(EventLoop* eloop, int fd):
    eloop_(eloop),
    fd_(fd),
    events_(0),
    revents_(0),
    index_(-1) {
}

void Channel::Update() {
   eloop_->UpdateChannel(this);
}

void Channel::HandleEvent() {
    if (revents_ & POLLNVAL) {
        std::cout << "Channel::HandleEvent() POLLNVAL" << std::endl;
    }

    if (revents_ & (POLLERR | POLLNVAL)) {
        if (this->error_cb_) {
            error_cb_();
        }
    }

    if (revents_ & (POLLIN | POLLPRI | POLLHUP)) {
        if (this->read_cb_) {
            read_cb_();
        }
    }

    if (revents_ & POLLOUT) {
        if (this->write_cb_) {
            write_cb_();
        }
    }
}

std::string Channel::EventsToString() {
    return EventsDebugString(fd_, events_);
}

std::string Channel::ReventsToString() {
    return EventsDebugString(fd_, revents_);
}

std::string Channel::EventsDebugString(int fd, int ev) {
    std::ostringstream os;
    os << fd << ": ";
    if (ev & POLLIN) {
        os << "IN ";
    }
    if (ev & POLLPRI) {
        os << "PRI ";
    }
    if (ev & POLLOUT) {
        os << "OUT ";
    }
    if (ev & POLLHUP) {
        os << "HUP ";
    }
    // if (ev & POLLRDHUP) {
    //     os << "RDHUP ";
    // }
    if (ev & POLLERR) {
        os << "ERR ";
    }
    if (ev & POLLNVAL) {
        os << "NVAL ";
    }
    return os.str();
}
