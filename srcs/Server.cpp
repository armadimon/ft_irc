#include "../includes/Server.hpp"

Server::Server()
{
	this->is_set = 0;
	this->fd = 0;

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
}

Server::~Server() {}

void Server::acceptClient()
{
	int					new_socket;
	struct sockaddr_in	new_socket_in;
	socklen_t			new_socket_len;

	new_socket_len = sizeof(new_socket_in);
	new_socket = accept(this->fd, (struct sockaddr *)&new_socket_in, &new_socket_len);
	if (new_socket == -1)
		throw std::runtime_error("Error: accept");
	clients[new_socket] = new Client(new_socket);
	std::cout << "Client #" << new_socket << " is Connected!" << std::endl;
	if (new_socket > fd_max)
		fd_max = new_socket;
	FD_SET(new_socket, &read_fds);
	FD_SET(new_socket, &write_fds);
}

void Server::createSocket()
{
	struct sockaddr_in	socket_in;
	struct protoent		*pe;

	pe = getprotobyname("tcp");
	if (pe == NULL)
		throw std::runtime_error("Error: getprotobyname");
	socket_in.sin_family = AF_INET;
	socket_in.sin_addr.s_addr = INADDR_ANY;
	socket_in.sin_port = htons(this->port);
	fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		throw std::runtime_error("Error: socket");
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (bind(fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) == -1)
		throw std::runtime_error("Error: bind");
	if (listen(fd, 42) == -1)
		throw std::runtime_error("Error: listen");
	FD_SET(fd, &read_fds);
	fd_max = fd;
}

void Server::doSelect() {
	is_set = select(fd_max + 2, &cpy_read_fds, &cpy_write_fds, NULL, NULL);
	// std::cout << "is_set : " << is_set << std::endl;
	if (is_set == -1)
		throw std::runtime_error("Error: select");
}

void	Server::removeClientFromChannel(int client_fd)
{
	std::map<std::string, Channel *>::iterator chIter = channels.begin();

	while (chIter != channels.end())
	{
		if (chIter->second->isExistClient(clients[client_fd]->getNickName()))
			chIter->second->removeClient(client_fd);
		if (chIter->second->getClientList().size() == 0)
		{
			delete chIter->second;
			channels.erase(chIter);
			chIter = channels.begin();
			continue;
		}
		chIter++;
	}
}

void Server::clientRead(int client_fd)
{
	int	r;
	char* bufRead = this->getClient(client_fd).getBuf();

  	r = recv(client_fd, bufRead, 1024, 0);
	std::cout << bufRead << std::endl;
  	if (r <= 0)
    {
		FD_CLR(client_fd, &read_fds);
		FD_CLR(client_fd, &write_fds);
    	close(client_fd);
		removeClientFromChannel(client_fd);
		std::map<int, Client *>::iterator mapIter = clients.find(client_fd);
		if (mapIter != clients.end())
		{
			delete clients[client_fd];
			clients.erase(mapIter);
		}
    	printf("client #%d gone away\n", client_fd);
		return ;
    }
	std::string tempStr(bufRead);
	memset(bufRead, 0, 4096);
	this->clients[client_fd]->parseMSG(this, tempStr);
}

void Server::run()
{
	createSocket();
	while (true)
	{
		cpy_read_fds = read_fds;
		cpy_write_fds = write_fds;
		doSelect();
		int i = 0;
		while (i < fd_max + 1 && is_set > 0)
		{
			if (FD_ISSET(i, &cpy_read_fds))
			{
				if (i == this->fd)
				{
					acceptClient();
					is_set--;
				}
				else
				{
					clientRead(clients[i]->getFD());
					is_set--;
				}
			}
			i++;
		}
	}
}

bool Server::isAlreadyUsed(std::string client_name)
{
	std::map<int, Client *>::iterator it = this->clients.begin();
	for (; it != this->clients.end(); it++)
		if ((*it).second->getNickName() == client_name)
			return true;
	return false;
}

/*
METHOD :: GETTER
*/

Client &Server::getClient(int client_fd)
{
	return (*(this->clients[client_fd]));
}

Client &Server::getClient(std::string name)
{
	std::map<int, Client *>::iterator it = this->clients.begin();
	for (; it != clients.end(); it++)
	{
		if (name == it->second->getNickName())
			return *(it->second);
	}
	throw std::runtime_error("Error :");
}

std::string	Server::getPass()
{
	return(password);
}

std::map<int, Client *> Server::getClients()
{
	return (clients);
}

std::map<std::string, Channel *> &Server::getChannels()
{
	return (channels);
}

Channel *Server::getChannel(std::string chName)
{
	if (isExistChannel(chName))
		return (channels[chName]);
	return (nullptr);
}

void Server::setChannel(std::string chName, int fd)
{

	this->channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, fd)));
}

void Server::setChannel(std::string chName, std::string key,int fd)
{

	this->channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, key, fd)));
}

/*ccccw
METHOD :: SETTER
*/

void Server::setPass(char *pw)
{
	this->password = pw;
}

void Server::setPort(char *port)
{
	this->port = atoi(port);
}

bool Server::isExistChannel(std::string channel_name)
{
	if (this->channels.find(channel_name) == this->channels.end())
		return false;
	return true;
}

// Channel *Server::findChannel(std::string name)
// {
// 	return this->channels.find(name)->second;
// }
