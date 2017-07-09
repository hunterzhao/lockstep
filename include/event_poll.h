#ifndef _EVENT_POLL_H_
#define _EVENT_POLL_H_

#include <sys/epoll.h>

#define EVENT_SIZE 10000
namespace game
{
class EventPoll
{
public:
    EventPoll();
    ~EventPoll();
    int registerHandler(int fd, int event, int et = true);
    int removeHandler(int fd);
    int modifyHandler(int fd, int event);
    
    int poll();
    struct epoll_event &getActiveEvent(int id);

private:
	int epoll_fd_;
    struct epoll_event events_[EVENT_SIZE];
};
}

#endif
