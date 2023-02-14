#include "../includes/Channel.hpp"

Channel::Channel() : name(), client_list() {}

Channel::Channel(std::string n) : name(n), client_list() {}

Channel::~Channel() {}

std::string Channel::getChannelName()
{
	return this->name;
}

std::map<int, Client*> Channel::getClientList()
{
	return this->client_list;
}

void Channel::addClient(int fd, Client* client)
{
	if (client == nullptr)
		exit(1);
	this->client_list.insert(std::make_pair(fd, client));
}

void Channel::removeClient(int fd)
{
	this->client_list.erase(fd);
}