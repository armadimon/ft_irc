#include "../../includes/Command.hpp"

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
			{
				int endPos = it->find_last_not_of("\n\r");
					c->setNickName(it->substr(0, endPos +1));
			}
			cnt++;
		}
	std::cout << "nick cmd : " << c->getNickName() << std::endl;
	}
}