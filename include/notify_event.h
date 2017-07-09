#ifndef _NOTIFY_EVENT_H_
#define _NOTIFY_EVENT_H_
#include <functional>
#include <string>
#include "socket_event.h"

namespace game
{
class Reactor;
class NotifyEvent : public SocketEvent 
{
public:
    NotifyEvent(Reactor* reactor, int fd);
    virtual ~NotifyEvent();
    
    int  init();
    int  onEvent(int event) override; 
    void close() override;
    void notify();
};
}

#endif
