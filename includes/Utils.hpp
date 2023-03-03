#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include "../includes/Server.hpp"

class Channel;
class Client;
class Server;

std::vector<std::string> string_split(std::string str, const char* delimiter);

std::string &ltrim(std::string &s, std::string delimiter);

std::string &rtrim(std::string &s, std::string delimiter);

const std::string &trim(std::string &s, std::string delimiter);

void broadcast(std::map<std::string, Channel *> tempCh, std::string chName, std::string msg, Server &s);

std::string	reply(int replyNum, std::string cName, std::string msg);

std::string	makePrefix(Client &c);

#endif