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
	char 				host_str[INET_ADDRSTRLEN];

	new_socket_len = sizeof(new_socket_in);
	new_socket = accept(this->fd, (struct sockaddr *)&new_socket_in, &new_socket_len);
	inet_ntop(AF_INET, &new_socket_in.sin_addr, host_str, INET_ADDRSTRLEN);
	if (new_socket == -1)
		throw std::runtime_error("Error: accept");
	clients[new_socket] = new Client(new_socket);
	clients[new_socket]->setHostName(host_str);
	std::cout << COLOR_GREEN "Client #" << new_socket << " is Connected!" COLOR_RESET << std::endl;
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
	socket_in.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_in.sin_port = htons(this->port);
	fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		throw std::runtime_error("Error: socket");
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (bind(fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) == -1)
		throw std::runtime_error("Error: bind");
	if (listen(fd, 5) == -1)
		throw std::runtime_error("Error: listen");
	FD_SET(fd, &read_fds);
	fd_max = fd;
}

void Server::doSelect() {
	is_set = select(fd_max + 1, &cpy_read_fds, &cpy_write_fds, NULL, NULL);
	if (is_set == -1)
		throw std::runtime_error("Error: select");
}

void	Server::removeClientFromChannel(Channel *channel, int client_fd)
{
	if (channel->isExistClient(clients[client_fd]->getNickName()))
		channel->removeClient(client_fd);
	if (channel->getClientList().size() == 0)
	{
		delete channel;
		channels.erase(channel->getChannelName());
	}
}

void	Server::removeClientFromAllChannels(int client_fd)
{
	std::map<std::string, Channel *>::iterator chIter = channels.begin();
	while (chIter != channels.end())
	{
		if (chIter->second->isExistClient(clients[client_fd]->getNickName()))
		{
			chIter->second->removeClient(client_fd);
		}
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
	char bufRead[513];

  	r = recv(client_fd, bufRead, 512, 0);
	if ( errno == EAGAIN )
	{
		errno = 0;
		return ;
	}
  	if (r <= 0)
    {
		FD_CLR(client_fd, &read_fds);
		FD_CLR(client_fd, &write_fds);
    	close(client_fd);
		removeClientFromAllChannels(client_fd);
		std::map<int, Client *>::iterator mapIter = clients.find(client_fd);
		if (mapIter != clients.end())
		{
			delete clients[client_fd];
			clients.erase(mapIter);
		}
		std::cout << COLOR_RED "client #";
		std::cout << client_fd;
		std::cout << " gone away" COLOR_RESET << std::endl;
		return ;
    }
	else
	{
		bufRead[r] = '\0';
		this->clients[client_fd]->parseMSG(this, bufRead);
	}
}

void Server::clientWrite(int client_fd)
{
	int	r;
	std::string msg = this->getClient(client_fd).getSendBuf();
	if (msg.length() <= 0)
		return ;
  	r = send(client_fd, msg.c_str(), msg.length(), 0);
	if ( errno == EAGAIN )
	{
		errno = 0;
		return ;
	}
  	if (r <= 0 || this->getClient(client_fd).getUserState() == LOGOFF)
    {
		FD_CLR(client_fd, &read_fds);
		FD_CLR(client_fd, &write_fds);
    	close(client_fd);
		removeClientFromAllChannels(client_fd);
		std::map<int, Client *>::iterator mapIter = clients.find(client_fd);
		if (mapIter != clients.end())
		{
			delete clients[client_fd];
			clients.erase(mapIter);
		}
    	std::cout << COLOR_RED "client #";
		std::cout << client_fd;
		std::cout << " gone away" COLOR_RESET << std::endl;
		return ;
    }
	this->getClient(client_fd).clearSendBuf();
}

void Server::run()
{
	createSocket();
	while (true)
	{
		FD_ZERO(&cpy_read_fds);
		FD_ZERO(&cpy_write_fds);
		cpy_read_fds = read_fds;
		cpy_write_fds = write_fds;
		doSelect();
		int i = 0;
		while (i < fd_max + 1 && is_set > 0)
		{
			if (FD_ISSET(i, &cpy_write_fds))
			{
				if (i != this->fd)
				{
					clientWrite(i);
					is_set--;
				}
			}
			if (FD_ISSET(i, &cpy_read_fds))
			{
				if (i == this->fd)
				{
					acceptClient();
					is_set--;
				}
				else
				{
					clientRead(i);
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

Client *Server::findClient(std::string name)
{
	std::map<int, Client *>::iterator it = this->clients.begin();
	for (; it != clients.end(); it++)
	{
		if (name == it->second->getNickName())
			return it->second;
	}
	return nullptr;
}

void Server::removeClient(int fd)
{
	std::map<int, Client *>::iterator it = this->clients.find(fd);
	this->removeClientFromAllChannels(fd);
	this->clients.erase(fd);
	delete (*it).second;
	close(fd);
	FD_CLR(fd, &read_fds);
	FD_CLR(fd, &write_fds);
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

/*
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
