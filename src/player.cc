#include <string.h>
#include "player.h"
#include "log.h"

namespace game
{
Player::Player(int id, int fd)
    : id_(id),
      fd_(fd),
      status_(ONLINE)
{}

void Player::send(std::string str)
{
    int ret = sendto(fd_, str.c_str(), str.size(), 0, (struct sockaddr *)&player_addr_, player_len_);
    if (ret < 0)
    {
    	DLOG(ERROR) << "send error";
    }
}

void Player::setAddress(struct sockaddr_in player_addr, socklen_t player_len)
{
    ::memcpy(&player_addr_, &player_addr, sizeof(sockaddr_in));
    ::memcpy(&player_len_, &player_len, sizeof(socklen_t));
}
}
