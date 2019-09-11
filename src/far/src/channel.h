#ifndef CHANNEL_H
#define CHANNEL_H

#include <poll.h>
#include <functional>

class EventLoop;

class Channel {
public:
    typedef std::function<void()> EventCallback;
    enum { 
        kNoneEvent = 0, 
        kReadEvent = POLLIN | POLLPRI,
        kWriteEvent = POLLOUT
    };

    Channel(EventLoop* eloop, int fd);

    void HandleEvent();

    void setReadCallback(const EventCallback& cb) {
        this->read_cb_ = cb;
    }

    void setWriteCallback(const EventCallback& cb) {
        this->write_cb_ = cb;
    }

    void setErrorCallback(const EventCallback& cb) {
        this->error_cb_ = cb;
    }

    int fd() const {
        return fd_;
    }

    int events() const {
        return events_;
    }

    void setRevents(const int revents) {
        this->revents_ = revents;
    }

    bool IsNoneEvent() const {
        return events_ == kNoneEvent;
    }

    void EnableRead() {
        events_ |= kReadEvent;
        this->Update();
    }
    void DisableRead() {
        events_ &= ~kReadEvent;
        this->Update();
    }

    void EnableWrite() {
        events_ |= kWriteEvent;
        this->Update();
    }
    void DisableWrite() {
        events_ &= ~kWriteEvent;
        this->Update();
    }

    void DisableAll() {
        events_ = kNoneEvent;
        this->Update();
    }

    int index() {
        return index_;
    }
    void setIndex(int index) {
        this->index_ = index;
    }

    EventLoop* OwnerLoop() {
        return this->eloop_;
    }

    // for debug
    std::string EventsToString();
    std::string ReventsToString();

private:
    void Update();
    static std::string EventsDebugString(int, int);
    
    int fd_;
    int events_;
    int revents_;
    int index_;

    EventLoop* eloop_;

    EventCallback read_cb_;
    EventCallback write_cb_;
    EventCallback error_cb_;
};

#endif // CHANNEL_H
