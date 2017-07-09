#include <unistd.h>
#include "notify_event.h"
#include "reactor.h"
#include "type.h"
#include "log.h"

namespace game
{
NotifyEvent::NotifyEvent(Reactor* reactor, int fd)
   : SocketEvent(reactor, fd)
{
    
}

NotifyEvent::~NotifyEvent()
{
    
}

int  NotifyEvent::init()
{
    setNoBlock();
    if (reactor_->registerHandler(this, EVENT_IN) < 0) 
    {
    	return -1;
    }
    return 1;
}

int  NotifyEvent::onEvent(int event)
{
    return 1;
} 

void NotifyEvent::close()
{
    DLOG(WARNING) << "remove event";
    reactor_->removeHandler(this);
    ::close(fd_);
}

void NotifyEvent::notify()
{
    uint64_t call = 1;
    int ret = ::write(fd_, &call, sizeof(call));
    if (ret < 0)
    {
        DLOG(ERROR) << "eventfd error";
    }
}
}
 
