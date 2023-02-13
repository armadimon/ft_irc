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

#define MAX_FD	1024

class Server
{
  public:
	Server();
	~Server();
	Client *getClient(int client_fd);
	void setClient(std::map<int, Client> c);
	void clientRead(int client_fd);
	void setPass(char *pw);
	void setPort(char *port);
	void createSocket();
	void doSelect();
	void acceptClient();
	void start();


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
	std::string password; // 서버 패스워드
};

#endif