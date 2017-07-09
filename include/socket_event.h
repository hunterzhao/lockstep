#ifndef _SOCKET_EVENT_
#define _SOCKET_EVENT_
/*
* 这个类顺便管理一下套接字的属性
*/
#include <memory>
#include <mutex>

namespace game 
{
class Reactor;
class SocketEvent 
{
public:
    SocketEvent(int fd);
    SocketEvent(Reactor* reactor, int fd);
    virtual ~SocketEvent();
    virtual int onEvent(int event) = 0;
    virtual void close() = 0;
    virtual int  init() = 0;
    void setEvent(int event) { event_ = event;};
    void setReactor(Reactor* reactor);
    int getFd() { return fd_;}
    void closeInNextLoop();
    
protected:    
    int setNoBlock();
    int reuseAddress();
    int resetOneShot();
    
protected:
    Reactor* reactor_ = nullptr;
    int fd_;
    int event_;
};
} // end of namespace
#endif
