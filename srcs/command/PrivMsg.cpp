#include "../../includes/Server.hpp"

void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);

	std::string temp = ":";

	if (c->getUserState() == REGISTER)
	{
		temp += c->getNickName();
		temp += "!";
		temp += c->getUserName();
		temp += "@";
		temp += c->getHostName();
		temp += " ";
		for (; it < str.end(); it++)
		{
			temp += *it;
			temp += " ";
		}
		send(c->getFD(), temp.c_str(), temp.size(), 0);
	}
}