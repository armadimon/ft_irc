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

void	cmdNick(Server *s, int fd, std::vector<std::string> str);
void	cmdPass(Server *s, int fd, std::vector<std::string> str);
void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str);
void	cmdUser(Server *s, int fd, std::vector<std::string> str);
void    cmdJoin(Client* c, std::vector<std::string> str);

#endif