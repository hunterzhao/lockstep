#include <string>
#include "game_unit.h"
#include "player.h"
#include "game_server.h"
#include "log.h"

namespace game
{
GameUnit::GameUnit(int unit_id, GameServer* server, int msecond)
   : unit_id_(unit_id),
     server_(server),
     msecond_(msecond), 
     actions_(new GameResProto()),
     game_status_(PREPARE)
{
    
}

GameUnit::~GameUnit()
{

}

void GameUnit::addPlayer(Player* player)
{
    players_in_unit_.insert(player);
}

std::string GameUnit::onGameMgr(int playerid, const UnitReqProto& unit)
{
    int type = unit.type();
    game::GameResProto res;
    switch(type)
    {
        case 0:
            {
                DLOG(INFO) << "start game";
                gameStart();
            }
            break;
        case 1:
            DLOG(INFO) << "end game";
            break;
    }
    res.set_type(3);
    res.set_code(1);
    std::string ans;
    assert(res.SerializeToString(&ans));
    return ans;
}

void GameUnit::onAction(int playerid, const ActionProto& action)
{ 
    DLOG(INFO) << "action coming";
    *(actions_->add_actions()) = action;
}

void GameUnit::gameStart()
{
   //register timer
   server_->setTimer(msecond_, std::bind(&GameUnit::onTimeUp, this));   
   game_status_ = START;
}


void GameUnit::broadCast(std::string msg)
{
   // broadcast msg
   for (auto player : players_in_unit_)
   {
        DLOG(INFO) << "send data to " << player->getid();
        player->send(msg);
   }
}

void GameUnit::onTimeUp()
{
   //TODO add frame id
   std::string message;
   actions_->set_type(4);
   assert(actions_->SerializeToString(&message));
   broadCast(message);
   actions_->Clear();
}

}
