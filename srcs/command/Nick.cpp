#include "../../includes/Client.hpp"

void	cmdNick(Client *c, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	int cnt = 0;

	for (; it < str.end(); it++)
	{
	std::cout << "nick cmd : " << *it << std::endl;
		if (cnt == 1)
			c->setNickName(*it);
		cnt++;
	}

	std::cout << "nick cmd : " << c->getNickName() << std::endl;
}