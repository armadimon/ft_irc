#include "../../includes/Command.hpp"

static std::string makeNameReply(std::string chName, std::string chMode)
{
	std::string str = "";

	str += chMode + " " + chName + " ";
	return (str);
}

static std::string makeEonReply(std::string chName)
{
	std::string str = "";

	str += chName + " ";
	return (str);
}

static std::string attachClientList(std::map<std::string, Channel *> tempCh, std::string chName, std::string nameReply)
{
	std::map<int, std::string> tempClient = tempCh[chName]->getClientList();
	std::map<int, std::string>::iterator clientIter = tempClient.begin();
	nameReply += ":";
	for (;clientIter != tempClient.end();)
	{
		std::string cname = clientIter->second;
		if (tempCh[chName]->getOperatorFD() == clientIter->first)
			nameReply += "@";
		nameReply += cname;
		clientIter++;
		if (clientIter != tempClient.end())
			nameReply += " ";
	}
	nameReply += "\r\n";
	return (nameReply);
}

// JOIN <channel>{,<channel>}
void cmdJoin(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	std::vector<std::string> channels_name;
	std::vector<std::string> channels_passwd;

	if (cmd.getParams().size() < 1)
		c.setSendBuf(reply(461, c.getNickName(), cmd.getCmd())); // 461 ERR_NEEDMOREPARAMS
    if (c.getUserState() == REGISTER)
    {
		channels_name = string_split(params[0], ",");
		if (params.size() > 1)
			channels_passwd = string_split(params[1], ",");

		std::vector<std::string>::iterator keyIter = channels_passwd.begin();
		for (size_t i = 0; i < channels_name.size(); i++)
		{
			if (channels_name[i].size() > 50 || channels_name[i].find("#") != 0)
			{
				c.setSendBuf(reply(476, c.getNickName(), channels_name[i]));   // ERR_BADCHANMASK 476
				return;
			}
			std::string key = keyIter < channels_passwd.end() ? *keyIter++ : "";
			std::map<std::string, Channel *> &tempCh = s.getChannels();
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);
	
			std::string nameReply = makeNameReply(channels_name[i], "=");
			std::string eonReply = makeEonReply(channels_name[i]);

			if (c.getmyChannelList().size() > 9 && c.findChannelFromList(channels_name[i]) == 0)
			{
				c.setSendBuf(reply(405, c.getNickName(), channels_name[i]));
				continue;
			}
			if (channels_name[i].size() > 0 && channels_name[i][0] != '#')
			{
				c.setSendBuf(reply(476, c.getNickName(), channels_name[i]));
				continue;
			}
			if (ChIt != tempCh.end())
			{
				if (s.getChannel(channels_name[i])->getPassword() != key)
				{
					c.setSendBuf(reply(475, c.getNickName(), channels_name[i]));
					continue;
				}
				s.getChannels()[channels_name[i]]->addClient(fd, c.getNickName());
				if (c.addmyChannelList(channels_name[i]) == 0)
					continue ;
			}
			else
			{
				// 새로 채널 만들기
				if (key != "")
					s.setChannel(channels_name[i], channels_passwd[i], fd);
				else
					s.setChannel(channels_name[i], fd);
				s.getChannels()[channels_name[i]]->addClient(fd, c.getNickName());
				c.addmyChannelList(channels_name[i]);
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			std::string	prefix = makePrefix(c);
			std::string msg = "";
			msg += prefix + "JOIN :" + channels_name[i] + "\r\n";
			broadcast(tempCh, channels_name[i], msg, s);
			nameReply = attachClientList(tempCh, channels_name[i], nameReply);
			c.setSendBuf(reply(353, c.getNickName(), nameReply));
			c.setSendBuf(reply(366, c.getNickName(), eonReply));
			if (keyIter < channels_passwd.end())
				keyIter++;
		}
    }
}