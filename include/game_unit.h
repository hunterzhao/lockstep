#ifndef GAME_UNIT_H_
#define GAME_UNIT_H_

#include <unordered_set>
#include <string>
#include "game.pb.h"

namespace game
{

class Player;
class GameServer;
class GameUnit
{
public:
    enum
    {
       PREPARE,
       START,
       END
    };
    GameUnit(int unit_id, GameServer* server, int msecond);
    
    ~GameUnit();
    
    std::string onGameMgr(int playerid, const UnitReqProto& unit);   

    void onAction(int playerid, const ActionProto& action);

    void gameStart();

    void gameEnd();    

    void broadCast(std::string msg);
    
    void onTimeUp();    
    
    void addPlayer(Player* player);    
    
private:
    int game_status_;
    int msecond_ = 0;
    std::unordered_set<Player*> players_in_unit_;
    game::GameResProto* actions_; //store player command or server command
    int unit_id_;
    GameServer* server_ = nullptr;
};
}
#endif
