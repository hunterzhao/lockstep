#ifndef _TIMER_EVENT_H_
#define _TIMER_EVENT_H_
#include "socket_event.h"
namespace game
{
class Reactor;
class TimerEvent : public SocketEvent
{
public:
    typedef std::function<void(void)> OnTimer;
    TimerEvent(Reactor* reactor, int fd, int msecond, OnTimer timer);
    virtual ~TimerEvent();
    
    int init();
    int onEvent(int event) override;
    void close() override;

    void excuteTimingTask();
private:
    int msecond_;
    OnTimer timer_;
};
}

#endif
