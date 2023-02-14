#include "../../includes/Server.hpp"

void	cmdNick(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);

	int cnt = 0;


	if (c->getUserState() == REGISTER)
	{
		for (; it < str.end(); it++)
		{
		std::cout << "nick cmd : " << *it << std::endl;
			if (cnt == 1)
				c->setNickName(*it);
			cnt++;
		}
	std::cout << "nick cmd : " << c->getNickName() << std::endl;
	}
}