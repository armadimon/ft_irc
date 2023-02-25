#include "../../includes/Command.hpp"

void	cmdPrivMsg(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);
	Server &s = cmd.getServer();

	std::string temp = ":";
	std::vector<int> reciverFD;
	std::vector<std::string> recivers;
	
	if (c.getUserState() == REGISTER)
	{
		temp += c.getNickName();
		temp += "!";
		temp += c.getUserName();
		temp += "@";
		temp += c.getHostName();
		temp += " ";

		recivers = string_split(params[0], ",");
		std::vector<std::string>::iterator rIter = recivers.begin();
		for (;rIter < recivers.end(); rIter++)
		{
			if ((*rIter)[0] == '#')
			{
				std::string tempStr = *rIter;
				std::cout << "PRIV check" << std::endl;
				// 
				std::map<std::string, Channel *> tempCh = s.getChannels();
				if (tempCh.size()  == 0)
					return ;
				std::map<int, std::string> tempCli = s.getChannels()[tempStr]->getClientList();
				std::map<int, std::string>::iterator clientIt = tempCli.begin();

				std::cout << "PRIV check 2" << std::endl;
				while (clientIt != tempCli.end())
				{

				std::cout << "PRIV check 3" << std::endl;
					if (clientIt->first != c.getFD())
						reciverFD.push_back(clientIt->first);
					clientIt++;
				}
			}
			else
			{
				std::map<int, Client *> temp_map = s.getClients();
				std::map<int, Client *>::iterator mapIter = temp_map.begin();

				for(; mapIter != temp_map.end(); mapIter++)
				{
					std::cout << "client : " << mapIter->second->getNickName() << std::endl;
					std::cout << "it : " << *rIter << std::endl;
					// std::cout << "priv msg : " << mapIter->second->getNickName() << std::endl;
					if (mapIter->second->getNickName() == *rIter)
					{
						reciverFD.push_back(mapIter->second->getFD());
					}
				}
			}
		}
		std::vector<int>::iterator vecIter = reciverFD.begin();
		for (; vecIter < reciverFD.end(); vecIter++)
		{
			std::cout << "vec iter : " << *vecIter << std::endl;
			temp += cmd.getCmd() + " " + params[0] + " ";
			if (params.size() > 1)
				temp += params[1];
			else
				temp += cmd.getTrailing();
			temp += "\r\n";
			std::cout << "temp : "  << temp << std::endl;
			send(*vecIter, temp.c_str(), temp.size(), 0);
		}
	}
}