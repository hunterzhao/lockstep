#include <assert.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <glog/logging.h>
#include "event_poll.h"
#include "type.h"
#include "log.h"

namespace game
{
EventPoll::EventPoll() : epoll_fd_(::epoll_create(1)) 
{
   assert(epoll_fd_ >= 0);
}

EventPoll::~EventPoll() 
{
	::close(epoll_fd_);
}

int EventPoll::registerHandler(int fd, int event, int et)
{
    struct epoll_event ev;
    ::memset(&ev, 0, sizeof(ev));  
    ev.data.fd = fd;
    ev.events = EPOLLERR | EPOLLHUP;
    if (et) ev.events |= EPOLLET;
    if (event & EVENT_IN)  ev.events |= EPOLLIN;
    if (event & EVENT_OUT) ev.events |= EPOLLOUT;
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev) < 0)
    {
        perror("epoll_ctl_add");
   	    return -1;
    }
    return 1;
}

int EventPoll::removeHandler(int fd)
{
    struct epoll_event ev;
    ::memset(&ev, 0, sizeof(ev)); 
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ev) < 0)
    {
    	perror("epoll_ctl_del");
    	return -1;
    }
    return 1;
}

int EventPoll::modifyHandler(int fd, int event)
{
    struct epoll_event ev;
    ::memset(&ev, 0, sizeof(ev));  
    ev.data.fd = fd;
    ev.events = EPOLLERR | EPOLLHUP | EPOLLET;
    if (event & EVENT_IN)  ev.events |= EPOLLIN;
    if (event & EVENT_OUT) ev.events |= EPOLLOUT;
    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev) < 0)
    {
        perror("epoll_ctl_mod");
   	    return -1;
    }
    return 1;
}

int EventPoll::poll()
{
	int num_events = ::epoll_wait(epoll_fd_, events_, EVENT_SIZE, 10000);
	if (num_events < 0)
	{
		if (errno != EINTR)
		{
            DLOG(ERROR) << "error";
			return -1;
		}

        //DLOG(ERROR) << "get intr, continue";
		return 0;
	}
	return num_events;
}

struct epoll_event& EventPoll::getActiveEvent(int id)
{
	if (id > EVENT_SIZE || id < 0)
	{
		//error
	    DLOG(ERROR) << "out of index";
		exit(-1);
	}
	return events_[id];
}
}
