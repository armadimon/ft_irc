#include "../../includes/Client.hpp"

void	cmdUser(Client *c, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	int cnt = 0;

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