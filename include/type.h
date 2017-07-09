#ifndef _TYPE_H_
#define _TYPE_H_
#include <sys/epoll.h>

/* 
* 位置 
*/
enum 
{
    EVENT_IN   = EPOLLIN,
    EVENT_OUT  = EPOLLOUT,
    EVENT_ERR  = EPOLLERR,
    EVENT_HUP  = EPOLLHUP,
    EVENT_ET   = EPOLLET,
    EVENT_ONESHOT = EPOLLONESHOT
};
#endif
