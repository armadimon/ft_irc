#include "../../includes/Command.hpp"

void	cmdPrivMsg(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);
	Server &s = cmd.getServer();

	std::string temp = makePrefix(c);
	std::vector<int> reciverFD;
	std::vector<std::string> recivers;
	
	if (c.getUserState() == REGISTER)
	{
		if (params[0].empty())
		{
			reply(fd, 411, NULL); // ERR_NORECIPIENT
			return;
		}
		if (params[1].empty())
		{
			reply(fd, 412, NULL); // ERR_NOTEXTTOSEND
			return;
		}
		recivers = string_split(params[0], ",");
		std::vector<std::string>::iterator rIter = recivers.begin();
		for (;rIter < recivers.end(); rIter++)
		{
			if ((*rIter)[0] == '#')
			{
				std::map<std::string, Channel *> tempCh = s.getChannels();
				if (tempCh.size()  == 0)
					return ;
				std::map<int, std::string> tempCli = s.getChannels()[*rIter]->getClientList();
				std::map<int, std::string>::iterator clientIt = tempCli.begin();
				while (clientIt != tempCli.end())
				{
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
			temp += cmd.getCmd() + " " + params[0] + " ";
			if (params.size() > 1)
				temp += params[1];
			else
				temp += cmd.getTrailing();
			temp += "\r\n";
			send(*vecIter, temp.c_str(), temp.size(), 0);
		}
	}
}