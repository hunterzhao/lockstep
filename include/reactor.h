#ifndef _REACTOR_H_
#define _REACTOR_H_

#include <map>
#include <queue>
#include <functional>
#include <memory>
#include <mutex>

namespace game
{
typedef std::function<void(void)> Task;

class EventPoll;
class SocketEvent;
class NotifyEvent;
class Reactor
{
public:
    Reactor();
    ~Reactor();
    int appendPollTask(Task&& task);
    int appendWorkTask(Task&& task);
    int loop();
    int registerHandler(SocketEvent* socket_event, int event, int et = true);
    int removeHandler(SocketEvent*  socket_event);
    int modifyHandler(SocketEvent* socket_event, int event); 
    int getHandlerNum();
    void notify();
    
private:
    EventPoll* event_poll_ = nullptr;
    std::map<int, SocketEvent*> socket_events_;
    NotifyEvent* notify_event_ = nullptr;
    std::queue<Task> tasks_;
    //std::mutex mtx_;
};
}

#endif
