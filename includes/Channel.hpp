#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "Server.hpp"
#include "Client.hpp"

class Channel
{
  public:
	Channel();
	Channel(std::string n);
	~Channel();
	std::string getChannelName();
	std::map<int, Client*> getClientList();
	void addClient(int fd, Client* client);
	void removeClient(int fd);
	// 채널로 PRIVMSG를 보내면, 채널이 해당 내용을 client_list에 PRIVMSG를 보내주는 함수

  private:
	std::string	name;
	std::map<int, Client*> client_list;
};

#endif