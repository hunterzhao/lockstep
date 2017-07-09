#ifndef GAME_SERVER
#define GAME_SERVER

#include <sys/socket.h>
#include <functional>
#include <unordered_map>
#include <string>

namespace game
{
class GameUnit;
class Player;
class Reactor;
class GameSocketEvent;
class GameServer
{
public:
    typedef std::function<void(void)> OnTimer;

    GameServer(Reactor* reactor);
   
    ~GameServer();
   
    int bind(int port);

    void detectPackage();    

    void createGameUnit(int unit_id);

    void doRequest(const std::string& msg, 
                   const struct sockaddr_in& player_addr, 
                   const socklen_t player_len);

    void plusPlayer(int id, 
                   const struct sockaddr_in& player_addr, 
                   const socklen_t player_len);

    void setTimer(int msecond, OnTimer timer);
    
    void broadCastAll(std::string msg);

private:
    int num_game_unit_ = 0;
    int num_player_ = 0;
    std::unordered_map<int, GameUnit*> game_units_;
    std::unordered_map<int, Player*> players_;
    GameSocketEvent *game_event_;
    Reactor* reactor_;
};
}
#endif
