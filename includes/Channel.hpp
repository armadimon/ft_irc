#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <map>
#include <utility>

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"

class Client;

class Channel
{
  public:
	Channel();
	Channel(std::string n, int user_fd);
	Channel(std::string n, std::string key, int user_fd);
	~Channel();
	int getOperatorFD();
	std::string getChannelName();
	std::string getPassword();
	void		setPassword();
	std::map<int, std::string> getClientList();
	void addClient(int fd, std::string clientName);
	void removeClient(int fd);
	void removeClient(std::string name);
	bool isExistClient(std::string name);
	// 채널로 PRIVMSG를 보내면, 채널이 해당 내용을 client_list에 PRIVMSG를 보내주는 함수

  private:
	std::string	name;
	std::string passwd;
	int oper_fd;
	std::map<int, std::string> client_list;
};

#endif