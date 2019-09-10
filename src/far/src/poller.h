#ifndef POLLOER_H
#define POLLOER_H

#include <vector>
#include <map>

struct pollfd;
class EventLoop;
class Channel;

class Poller {
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* );

    ~Poller();

    int64_t Poll(int timeout, ChannelList* active_channels);

    void UpdateChannel(Channel* channel);

    void AssertInLoopThread();

private:
    void FillActiveChannels(int num_events, ChannelList* active_channels) const;

    EventLoop* eloop_;
    std::vector<struct pollfd> pollfds_;
    std::map<int, Channel*> channel_map_;

    // No copying allowed!
    Poller(const Poller&);
    void operator=(const Poller&);
};

#endif // POLLOER_H
