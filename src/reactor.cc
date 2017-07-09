#include <sys/eventfd.h>
#include "reactor.h"
#include "event_poll.h"
#include "socket_event.h"
#include "notify_event.h"
#include "type.h"
#include "assert.h"
#include "log.h"

namespace game 
{
Reactor::Reactor()
  : event_poll_(new EventPoll())
{ 
    notify_event_ = new NotifyEvent(this, eventfd(0, 0));
    notify_event_->init();
}

Reactor::~Reactor() 
{
    socket_events_.clear();
    DLOG(INFO) << "reactor delete";
    if (notify_event_ != nullptr)
       delete notify_event_;
    if (event_poll_ != nullptr)
       delete event_poll_;
}

int Reactor::appendPollTask(Task&& task)
{
   // std::lock_guard<std::mutex> lk(mtx_);
    tasks_.push(std::move(task));
    notify();
    return 1;
}

int Reactor::appendWorkTask(Task&& task)
{
    return 1;
}

int Reactor::loop()
{
    // std::queue<Task> tasks;
    // {
    //     std::lock_guard<std::mutex> lk(mtx_);
    //     tasks_.swap(tasks);
    // }

	while(!tasks_.empty())
	{
		Task t = tasks_.front();
        tasks_.pop();
		t();	
	}
    
    if (!socket_events_.empty())
    {
    	int num_events = event_poll_->poll();
    	if (num_events < 0)
    	{
    		return -1;
    	}
    	else 
    	{
    		for (int i = 0; i < num_events; i++)
    		{
    			struct epoll_event &ev = event_poll_->getActiveEvent(i);
    			int fd = ev.data.fd;
    			int event = 0;
    			if (ev.events & EPOLLIN) event |= EVENT_IN;
    			if (ev.events & EPOLLOUT)event |= EVENT_OUT;
    			if (ev.events & (EPOLLHUP | EPOLLERR)) event |= EVENT_ERR;
    			if (socket_events_.find(fd) == socket_events_.end())
                {
                    event_poll_->removeHandler(fd);
                    continue;
                }

                SocketEvent* socket_event = socket_events_[fd];
    			socket_event->onEvent(event);
    		}
    	}
    }
    return 1;
}

int Reactor::registerHandler(SocketEvent* socket_event, int event, int et)
{
    if (event_poll_->registerHandler(socket_event->getFd(), event, et) < 0)
    {
    	//error
    	return -1;
    }
    socket_event->setEvent(event);
    socket_events_[socket_event->getFd()] = socket_event;
    DLOG(INFO) << "register new handle " << socket_events_.size();
    return 1;
}

int Reactor::removeHandler(SocketEvent* socket_event)
{
    int index = socket_event->getFd();
    assert(socket_events_.find(index) != socket_events_.end());
    if (event_poll_->removeHandler(socket_event->getFd()) < 0)
    {
    	return -1;
    }
    
    socket_events_.erase(index);
    DLOG(WARNING) << "after remove, " << socket_events_.size() << " handler left";
    if (socket_events_.size() == 0)
    {

        DLOG(ERROR) << "handler is all empty";
    }
    return 1;
}

int Reactor::modifyHandler(SocketEvent* socket_event, int event)
{
    if (socket_events_.find(socket_event->getFd()) == socket_events_.end())
        return -1;
    
    if (event_poll_->modifyHandler(socket_event->getFd(), event) < 0)
    {
    	return -1;
    }
    socket_events_[socket_event->getFd()]->setEvent(event);
    DLOG(INFO) << "modify one handle " << socket_events_.size();
    return 1;
} 

int Reactor::getHandlerNum()
{
    return socket_events_.size();
}

void Reactor::notify()
{
    notify_event_->notify();
    DLOG(INFO) << "one notify add";
}
}
