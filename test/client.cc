#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <ctime>

#include <vector>
#include <thread>
#include <string>
#include <chrono> 
#include "game.pb.h"

int socketfd;
struct sockaddr_in server_addr;
socklen_t addr_size;

//int64_t current_millis()
//{
//    struct timeval tv;
//    ::gettimeofday(&tv, NULL);
//    return (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
//}
int run = 1;
void HandleSignal(int sig) {
    printf("stop\n");
    printf("signal %d\n", sig);
    run = 0;
}

void send(const std::string& msg)
{
    int n = ::sendto(socketfd, msg.c_str(), msg.size(), 0, (struct sockaddr *)&server_addr, addr_size);
    if (n < 0)
    {
       perror("send error\n");
    }
}

void recv(std::string& res)
{
    char buffer[1024];
    int n = ::recvfrom(socketfd, buffer, 1024, 0, nullptr, nullptr);
    if (n < 0)
    {
       perror("recv error\n");
    }
    res = std::string(buffer, n);
}

void playerLogin()
{
    std::string login_req;
    game::GameReqProto req;
    req.set_type(1);
    assert(req.SerializeToString(&login_req) == true);
    send(login_req);
}

void lobbyCreate(int unit_id)
{
    std::string login_lobby;
    game::GameReqProto req;
    req.set_type(0);
    req.set_unitid(unit_id);
    assert(req.SerializeToString(&login_lobby));
    send(login_lobby);
    
    // std::string ans;
    // game::GameResProto res;
    // recv(ans);
    // assert(res.ParseFromString(ans));
    // assert(res.type() == 0);
    // assert(res.code() == 1);
}

void addPlayer(int unitid, int playerid)
{
    std::string add_player;
    game::GameReqProto req;
    req.set_type(2);
    req.set_unitid(unitid);
    req.set_playerid(playerid);
    assert(req.SerializeToString(&add_player));
    send(add_player);
  
    // std::string ans;
    // game::GameResProto res;
    // recv(ans);
    // assert(res.ParseFromString(ans));
    // assert(res.type() == 2);
    // assert(res.code() == 1);
}

void startGame(int unitid)
{
    std::string start_game;
    game::GameReqProto req;    
    req.set_type(3);
    req.set_unitid(unitid);
    req.set_playerid(0);
    game::UnitReqProto* unit = new game::UnitReqProto();
    unit->set_type(0);
    req.set_allocated_unitreq(unit);
    assert(req.SerializeToString(&start_game));
    send(start_game);
    
    // std::string ans;
    // game::GameResProto res; 
    // recv(ans);
    // assert(res.ParseFromString(ans));
    // assert(res.type() == 3);
    // assert(res.code() == 1);
}

void walk(int unitid, int playerid)
{
    std::string walk_str;
    game::GameReqProto req;    
    req.set_type(4);
    req.set_unitid(unitid);
    req.set_playerid(playerid);
    game::ActionProto* action = new game::ActionProto();
    action->set_playerid(playerid);
    action->set_type(5); //walk
    req.set_allocated_actionreq(action);
    assert(req.SerializeToString(&walk_str));
    send(walk_str);
}

void waitmsg()
{
    std::string ans;
    
    while(run)
    {
       printf("wait for msg from server\n");
       recv(ans);//assert(res.ParseFromString(ans));
       std::cout << "new message coming" <<std::endl;;
       game::GameResProto res;
       assert(res.ParseFromString(ans));
       switch(res.type())
       {  
          case 0:
            std::cout << "new game unit created" <<std::endl;
            break;
          
          case 1:
          {
            assert(res.type() == 1);
            assert(res.code() == 1);
            game::PlayerInfoProto player = res.playerinfo();
            std::cout <<  player.playerid() << "new player login" <<std::endl;
          }
          break;

          case 2:
            std::cout << "new player add in game unit" <<std::endl;
            break;
          case 3:
            std::cout << "game logic" << std::endl;
            break;
          case 4:
            for (int i = 0; i < res.actions_size(); i++) 
            {
                std::cout << "player " 
                        << res.actions(i).playerid() 
                        << "type " 
                        << res.actions(i).type() << std::endl;
            }
       }
       
    }
    run = 1;
    
}

void test(int port)
{
    socketfd = ::socket(PF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ::memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
    addr_size = sizeof(server_addr);
    
    int option = 0;

    while(std::cin >> option)
    {
        switch (option)
        {
        case 0:
            playerLogin(); 
            break;
        case 1:
            {
            int unitid= 0;
            std::cout << "unit number:";
            std::cin >> unitid;
            lobbyCreate(unitid);
            std::cout << unitid << "unit create success" <<std::endl;
            }
            break;
        case 2:
            {
            int playerid, unitid;
            std::cout << "join game! playerid & unitid :";
            std::cin >> playerid >> unitid;
            addPlayer(unitid, playerid);
            std::cout << unitid << "unit join success" <<std::endl;
            }
            break;
        case 3:
            {
            int unitid;
            std::cin >> unitid;
            startGame(unitid);
            std::cout << unitid << "unit game start" <<std::endl;
            }
            break;
        case 4:
            {
            std::cout << "walk playerid && unitid: " <<std::endl;
            int playerid, unitid;
            std::cin >>  playerid >> unitid;
            walk(unitid, playerid);
            }
        }
        //waitmsg();
        printf("wait for next option\n");
    }
}

int main(int argc, char *argv[])
{
    //signal(SIGINT, HandleSignal);
    int port = 8899;
    std::thread th(waitmsg);
    test(port);
    th.join();
    
    return 0;
}
