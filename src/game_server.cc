#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/timerfd.h>
#include <time.h>
#include <stdlib.h>
#include <functional>
#include <iostream>
#include <string>
#include "timer_event.h"
#include "game_socket_event.h"
#include "game_unit.h"
#include "log.h"
#include "game_server.h"
#include "player.h"
#include "game.pb.h"

#define MAX_BUFFER_SIZE 1024 * 2
namespace game
{
GameServer::GameServer(game::Reactor* reactor)
   : reactor_(reactor)
{
    num_player_ = 0;
}

GameServer::~GameServer() 
{
    if (game_event_ != nullptr)
       delete game_event_;
}

int GameServer::bind(int port)
{
    int udp_fd = ::socket(AF_INET, SOCK_DGRAM, 0); 
    game_event_ = new GameSocketEvent(reactor_, udp_fd, port,
                      std::bind(&GameServer::detectPackage, this));

    if (game_event_->init() < 0)
    {
        return -1;
    }
    return 1;
}

void GameServer::detectPackage()
{
    char data[MAX_BUFFER_SIZE];
    struct sockaddr_in player_addr;
    socklen_t player_len = sizeof(sockaddr_in);
    int  len = ::recvfrom(game_event_->getFd(), data, 
               MAX_BUFFER_SIZE, 0, (struct sockaddr *)&player_addr, &player_len);

    if (len < 0)
    {
        DLOG(ERROR) << "udp recv error";
    }
    std::string msg(data, len);
    doRequest(msg, player_addr, player_len);
}

void GameServer::createGameUnit(int unit_id)
{
    // check if already create

    GameUnit* unit = new GameUnit(unit_id, this, 10000);
    game_units_[unit_id] = unit;
    DLOG(INFO) << unit_id  << "game unit created";
}

void GameServer::
plusPlayer(int id, 
           const struct sockaddr_in& player_addr, 
           const socklen_t player_len)
{
    Player* player = new Player(id, game_event_->getFd());
    player->setAddress(player_addr, player_len);
    players_[id] = player;
}

void GameServer::doRequest(const std::string& msg, 
                           const struct sockaddr_in& player_addr, 
                           const socklen_t player_len)
{
    //dp parse
    game::GameReqProto req;
    assert(req.ParseFromString(msg) == true);
    int unit_id   = req.unitid();
    int type      = req.type();
    int player_id = req.playerid();
    game::GameResProto res;
    std::string res_str;
    switch (type)
    {
        case 0: //in lobby
            {   // wide broadcast
                //TODO create unit
                createGameUnit(unit_id);
                res.set_type(0);
                res.set_code(1);
                assert(res.SerializeToString(&res_str) == true);
                broadCastAll(res_str);
            }
            break;
        case 1: //login player
            {   //wide broadcast
                plusPlayer(num_player_, player_addr, player_len);              
                LOG(INFO) << "new player login in";
                res.set_type(1);
                res.set_code(1);
                PlayerInfoProto* player_info = new PlayerInfoProto();
                player_info->set_playerid(num_player_);
                res.set_allocated_playerinfo(player_info);
                assert(res.SerializeToString(&res_str) == true);
                broadCastAll(res_str);
                num_player_++;
            }
            break;
        case 2: //in lobby
            {
                // add player
                // wide broadcast
                game_units_[unit_id]->addPlayer(players_[player_id]);
                res.set_type(2);
                res.set_code(1);
                assert(res.SerializeToString(&res_str) == true);
                broadCastAll(res_str); 
            }
            break;
        case 3: // game logic
            {   // wide broadcast
                //TODO detail job send to game unit
                UnitReqProto unit = req.unitreq();
                res_str = 
                game_units_[unit_id]->onGameMgr(player_id, unit);        
                broadCastAll(res_str);  
            }
            break;
       case 4: // single player action 
            {
                ActionProto action = req.actionreq();
                game_units_[unit_id]->onAction(player_id, action);
            }
    }
}

void GameServer::setTimer(int msecond, OnTimer timer)
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd < 0) 
    {
       DLOG(ERROR) << "timer fd error";
    }
    TimerEvent* timer_event_ = new TimerEvent(reactor_, fd, msecond, timer);
    timer_event_->init();
}

void GameServer::broadCastAll(std::string msg)
{
    for (auto item : players_)
    {
        item.second->send(msg);
    }
}
}
