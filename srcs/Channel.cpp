#include "../includes/Channel.hpp"

Channel::Channel() : name(), passwd(), oper_fd(), client_list() {}

Channel::Channel(std::string n, int user_fd) : name(n), oper_fd(user_fd), client_list() {}

Channel::~Channel() {}

std::string Channel::getChannelName()
{
	return this->name;
}

std::string Channel::getPassword()
{
	return this->passwd;
}

int Channel::getOperatorFD()
{
	return this->oper_fd;
}

std::map<int, std::string> Channel::getClientList()
{
	return this->client_list;
}

void Channel::addClient(int fd, std::string clientName)
{
	// if (clientName == nullptr)
	// 	exit(1);
	this->client_list.insert(std::make_pair(fd, clientName));
}

void Channel::removeClient(int fd)
{
	this->client_list.erase(fd);
}

void Channel::removeClient(std::string name)
{
	std::map<int, std::string>::iterator it = this->client_list.begin();
	for (; it != this->client_list.end(); it++)
	{
		if (name == (*it).second)
			this->client_list.erase(it);
	}
}

bool Channel::isExistClient(std::string name)
{
	std::map<int, std::string>::iterator it = this->client_list.begin();
	for (; it != this->client_list.end(); it++)
		if (name == (*it).second)
			return true;
	return false;
}