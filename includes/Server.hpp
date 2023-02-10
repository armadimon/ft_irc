#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Client.hpp"

#define MAX_FD	1024

class Server
{
  public:
	Server();
	~Server();
	Client getClient();
	void setClient(std::map<int, Client> c);
	void setPass(char *pw);
	void setPort(char *port);
	void createSocket();
	void acceptClient();
	void start();

  private:
	int			fd;
	int			port;
	std::map<int, Client> clients;
	std::string password; // 서버 패스워드
};

#endif