#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>


#include "Client.hpp"
#include "Utils.hpp"
#include "Channel.hpp"

#define MAX_FD	1024

class Channel;

class Server
{ 	
  public:
	Server();
	~Server();
	Client &getClient(int client_fd);
	Client &getClient(std::string name);
	std::map<int, Client *> getClients();
	bool isNotUsed(std::string client_name);
	std::map<std::string, Channel *> &getChannels();
	Channel *getChannel(std::string chName);
	void setChannel(std::string chName, int fd);
	void addChannel();
	void setClient(std::map<int, Client> c);
	void clientRead(int client_fd);
	std::string	getPass();
	void setPass(char *pw);
	void setPort(char *port);
	void createSocket();
	void doSelect();
	void acceptClient();
	void run();
	bool isExistChannel(std::string channel_name);

  private:
	int			fd;
	int			fd_max;
	int			fd_num;
	int			port;
	int			is_set;
	fd_set		cpy_read_fds;
	fd_set		cpy_write_fds;
	fd_set		read_fds;
	fd_set		write_fds;

	std::map<int, Client *> clients;
	std::map<std::string, Channel *> channels;

	std::string password; // 서버 패스워드
};

#endif