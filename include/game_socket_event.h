#ifndef _LBS_SOCKET_EVENT_H_
#define _LBS_SOCKET_EVENT_H_
#include <functional>
#include <string>
#include "socket_event.h"
#include "reactor.h"

namespace game
{
class Reactor;
class GameSocketEvent : public SocketEvent
{
public:
    typedef std::function<void(void)> Requestor;
    GameSocketEvent(int fd, int id, Requestor requestor);
    GameSocketEvent(Reactor* reactor, int fd, int port, Requestor requestor);
    virtual ~GameSocketEvent();
    virtual void close() override;   
    int  init() override;
    int  onEvent(int event) override; 

private:
    int  dataIn();
    int  dataOut();

private:
    Requestor requestor_;
    int player_id_;
    int port_;
};
}

#endif
