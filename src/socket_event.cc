#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <functional>
#include <stdio.h>
#include "socket_event.h"
#include "reactor.h"
#include "type.h"
#include "log.h"

namespace game
{
SocketEvent::SocketEvent(int fd)
    : fd_(fd)
{

}

SocketEvent::SocketEvent(Reactor* reactor, int fd) 
    : reactor_(reactor), 
      fd_(fd)
{

}

SocketEvent::~SocketEvent() 
{
    event_ = 0;
}

void SocketEvent::closeInNextLoop()
{
    DLOG(WARNING) << "close in next loop";
    reactor_->appendPollTask(std::move(std::bind(&SocketEvent::close, this)));
}

int SocketEvent::setNoBlock()
{
    int opts = ::fcntl(fd_, F_GETFL);
    if (opts < 0)
    {
        DLOG(ERROR) << "fcntl sock failed";
        exit(1);
    }
    opts = opts | O_NONBLOCK;
    if (::fcntl(fd_, F_SETFL, opts) < 0)
    {
	DLOG(ERROR) << "fcntl sock failed";
	exit(1);
    }
    return 1;
}

int SocketEvent::reuseAddress()
{
    int reuse = 1;
    if (::setsockopt(fd_, SOL_SOCKET, 
    	SO_REUSEADDR, &reuse, sizeof(reuse)) > 0)
    {
        DLOG(ERROR) << "exit reuse address";
    	exit(-1);
    }
    return 1;
}

void SocketEvent::setReactor(Reactor* reactor) 
{ 
    if (reactor_ == nullptr) 
    {
        DLOG(INFO) << "reactor is set correct";
        reactor_ = reactor; 
    }
    else 
    {
        DLOG(ERROR) << "reactor is not null";
    }
}
}
