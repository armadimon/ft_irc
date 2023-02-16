#include "../../includes/Command.hpp"

void	cmdUser(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);
	int cnt = 0;

	if (c->getUserState() == REGISTER)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
				c->setUserName(*it);
			else if (cnt == 2)
				c->setHostName(*it);
			else if (cnt == 3)
				;
			else if (cnt == 4)
				c->setRealName(*it);
			cnt++;
		}
		std::cout << "User cmd : " << c->getUserName() << std::endl;
		std::cout << "User cmd : " << c->getHostName() << std::endl;
		std::cout << "User cmd : " << c->getRealName() << std::endl;
	}
}