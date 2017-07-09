#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <iostream>
#include "reactor.h"
#include "game_socket_event.h"
#include "type.h"
#include "log.h"

namespace game
{
GameSocketEvent::GameSocketEvent(int fd, int id, Requestor requestor)
    : SocketEvent(fd),
      player_id_(id),
      requestor_(requestor)
{
    
}

GameSocketEvent::GameSocketEvent(Reactor* reactor, int fd, int port, Requestor requestor)
    : SocketEvent(reactor, fd),
      port_(port),   
      requestor_(requestor)
{}

GameSocketEvent::~GameSocketEvent()
{
    //printf("lbs socket event delete\n");
}

int GameSocketEvent::init()
{
    setNoBlock();
    struct sockaddr_in addr;  
    DLOG(INFO) << "waiting for client...";  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(8899);  
    addr.sin_addr.s_addr = ::htonl(INADDR_ANY);  
    ::bzero(&(addr.sin_zero), sizeof(addr.sin_zero));   
    int ret = ::bind(getFd(), (struct sockaddr *)&addr, sizeof(addr));  
    if (ret < 0)
    {  
        perror("bind error");  
        DLOG(ERROR) << "error";
    }  
    if (reactor_->registerHandler(this, EVENT_IN) < 0) 
    {
    	return -1;
    }
    return 1;
}

int GameSocketEvent::onEvent(int event)
{
    if (event & EVENT_HUP)
    {
        DLOG(ERROR) << "hup";
        closeInNextLoop();
        return -1;
    }
    if (event & EVENT_ERR)
    {
        DLOG(INFO) << "error";
        closeInNextLoop();
        return -1;
    }

    if (event & EVENT_IN)
    {
        DLOG(INFO) << "event in";
        if (dataIn() < 0)
        {
            closeInNextLoop();
            return -1;
        }
    }
    return 1;
}

void GameSocketEvent::close()
{
    //DLOG(ERROR) << "remove event";
    reactor_->removeHandler(this);
    ::close(fd_);
    delete this;
}

int GameSocketEvent::dataIn()
{
    //printf("start read \n");
    requestor_();
    reactor_->modifyHandler(this, EVENT_IN);
    return 1;
}
}
