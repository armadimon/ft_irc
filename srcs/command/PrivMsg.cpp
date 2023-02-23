#include "../../includes/Command.hpp"

void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client &c = s->getClient(fd);

	std::string temp = ":";
	std::vector<int> reciver;

	int cnt = 0;
	if (c.getUserState() == REGISTER)
	{
		temp += c.getNickName();
		temp += "!";
		temp += c.getUserName();
		temp += "@";
		temp += c.getHostName();
		temp += " ";
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
			{
				if ((*it).find("#") != std::string::npos)
				{
					std::string tempStr = *it;
					std::cout << "PRIV check" << std::endl;
					std::map<int, std::string> tempCli = s->getChannels()[tempStr]->getClientList();
					std::map<int, std::string>::iterator clientIt = tempCli.begin();

					std::cout << "PRIV check 2" << std::endl;
					while (clientIt != tempCli.end())
					{

					std::cout << "PRIV check 3" << std::endl;
						if (clientIt->first != c.getFD())
							reciver.push_back(clientIt->first);
						clientIt++;
					}
				}
				else
				{
				std::map<int, Client *> temp_map = s->getClients();
				std::map<int, Client *>::iterator mapIter = temp_map.begin();

				for(; mapIter != temp_map.end(); mapIter++)
				{
					std::cout << "client : " << mapIter->second->getNickName() << std::endl;
					std::cout << "it : " << *it << std::endl;
					// std::cout << "priv msg : " << mapIter->second->getNickName() << std::endl;
					if (mapIter->second->getNickName() == *it)
					{
						reciver.push_back(mapIter->second->getFD());
					}
				}
				}
			}
			temp += *it;
			if (it + 1 != str.end())
				temp += " ";
			cnt++;
		}
		std::vector<int>::iterator vecIter = reciver.begin();
		std::cout << "temp : "  << temp << std::endl;
		for (; vecIter < reciver.end(); vecIter++)
		{
			std::cout << "vec iter : " << *vecIter << std::endl;
			send(*vecIter, temp.c_str(), temp.size(), 0);
		}
	}
}