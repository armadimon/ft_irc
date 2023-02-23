#include "../../includes/Command.hpp"

void	cmdPass(Server *s, int fd, std::vector<std::string> str)
{
	// if (str.size() < 1) // ERR_NEEDMOREPARAMS 461
	std::vector<std::string>::iterator it = str.begin();
	Client &c = s->getClient(fd);

	int cnt = 0;

	if (c.getUserState() == DEFAULT)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
			{
				int endPos = it->find_last_not_of("\n\r");
				
				std::cout << "server_pass : [" << s->getPass() << std::endl;
				std::cout << "input_pass : [" << it->substr(0, endPos + 1) << std::endl;

				if (s->getPass() == it->substr(0, endPos +1))
					c.setUserState();
				std::cout << "State : " << c.getUserState() << std::endl;
				// std::string temp;
				// temp = 
				// if (s->getPass() == *it)
			}
			cnt++;
		}
	}
	if (c.getUserState() == REGISTER)
		; // ERR_ALREADYREGISTRED 462 
}