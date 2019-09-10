#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <thread>
#include <vector>
#include <cassert>
#include <memory>

class Poller;
class Channel;

class EventLoop {
public:
    typedef std::vector<Channel*> ChannelList;
    enum { kPollTimeout = 2 };

    EventLoop();
    ~EventLoop();

    void Loop();

    void AssertInLoopThread() {
        if (thread_id_ != std::this_thread::get_id()) {
            abort();
        }
    }

    void Quit();

    void UpdateChannel(Channel*);
private:

    bool quit_;
    bool is_loop_;
    std::thread::id thread_id_;
    ChannelList active_channels_;
    std::shared_ptr<Poller> poller_;

    // No copying allowed
    EventLoop(const EventLoop&);
    void operator=(const EventLoop&);
};

#endif // EVENT_LOOP_H
