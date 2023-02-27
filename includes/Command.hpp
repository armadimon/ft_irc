#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <map>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

class Server;
class Client;

class Command
{
  public:
	Command();
	Command(std::string msg, Server *server);
	~Command();

	Server &getServer();
	std::vector<std::string> &getParams();
	std::string getCmd();
	std::string	getTrailing();

  private:
	std::string	cmd;
	std::vector<std::string> params;
	std::string trailing;
	Server	*server;
};

void	cmdPass(Command cmd, int fd);
void	cmdUser(Command cmd, int fd);
void	cmdNick(Command cmd, int fd);
void	cmdPrivMsg(Command cmd, int fd);
void	cmdJoin(Command cmd, int fd);
void	cmdKick(Command cmd, int fd);
void	cmdPart(Command cmd, int fd);

#endif

