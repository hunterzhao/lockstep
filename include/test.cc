//#include <stdio.h>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
//#include <stdlib.h>

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
 
 private:
     struct sockaddr_in player_addr_;
     socklen_t player_len_;
     int id_ = 0;
     int fd_ = -1;
     int status_;
};

int main()
{
   struct sockaddr_in player_addr;
   Player player(1,2);
   
}
