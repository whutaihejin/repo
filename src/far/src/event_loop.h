#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <thread>
#include <cassert>

class EventLoop {
public:

    EventLoop();
    ~EventLoop();

    void Loop();

    void AssertInLoopThread() {
        if (thread_id_ != std::this_thread::get_id()) {
            abort();
        }
    }

private:
    bool is_loop_;
    std::thread::id thread_id_;

    // No copying allowed
    EventLoop(const EventLoop&);
    void operator=(const EventLoop&);
};

#endif // EVENT_LOOP_H
