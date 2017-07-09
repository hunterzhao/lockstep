#ifndef PLAYER_H_
#define PLAYER_H_
#include <netinet/in.h>
#include <string>

namespace game
{
class Player
{
public:
    enum
    {
      ONLINE,
      OFFLINE
    };
    Player(int id, int fd);
    ~Player();
    void setAddress(struct sockaddr_in player_addr, socklen_t player_len);
    void send(std::string);  
    int  getid() { return id_;} 

private:
    struct sockaddr_in player_addr_;
    socklen_t player_len_;
    int id_ = 0;
    int fd_ = -1;
    int status_;
};
}
#endif
