#include "../../includes/Command.hpp"

// NOTICE <nickname> <text>
void	cmdNotice(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	std::string temp = makePrefix(c);
	std::vector<int> reciverFD;
	std::vector<std::string> recivers;

	if (c.getUserState() == REGISTER)
	{
		if (params[0].empty())
		{
			c.setSendBuf(reply(411, c.getNickName(), ""));  // ERR_NORECIPIENT
			return;
		}
		if (params[1].empty())
		{
			c.setSendBuf(reply(412, c.getNickName(), "")); // ERR_NOTEXTTOSEND
			return;
		}
		recivers = string_split(params[0], ",");
		std::vector<std::string>::iterator rIter = recivers.begin();
		for (;rIter < recivers.end(); rIter++)
		{
			if ((*rIter)[0] == '#')
			{
				std::map<std::string, Channel *> tempCh = s.getChannels();
				if (!s.isExistChannel(*rIter))
					c.setSendBuf(reply(403, c.getNickName(), *rIter));
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
				Client *tmp_client = s.findClient(*rIter);
				if (tmp_client != nullptr)
					reciverFD.push_back(tmp_client->getFD());
				else
					c.setSendBuf(reply(401, c.getNickName(), *rIter));
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
			s.getClient(*vecIter).setSendBuf(temp);
		}
	}
}