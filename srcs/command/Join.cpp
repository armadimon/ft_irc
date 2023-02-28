#include "../../includes/Command.hpp"

static std::string makeNameReply(std::string nickName, std::string chName, std::string chMode)
{
	std::string str = "";

	str += nickName + " " + chMode + " " + chName + " ";
	return (str);
}

static std::string makeEonReply(std::string nickName, std::string chName)
{
	std::string str = "";

	str += nickName + " " + chName + " ";
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

void cmdJoin(Command cmd, int fd)
{
	// if (str.size() < 1) 461 ERR_NEEDMOREPARAMS
	std::vector<std::string> params = cmd.getParams();
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	std::vector<std::string> channels_name;
	std::vector<std::string> channels_passwd;

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
				reply(fd, 476, channels_name[i]);   // ERR_BADCHANMASK 476
				return;
			}
			std::string key = keyIter < channels_passwd.end() ? *keyIter++ : "";
			std::map<std::string, Channel *> &tempCh = s.getChannels();
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);
	
			std::string nameReply = makeNameReply(c.getNickName(), channels_name[i], "=");
			std::string eonReply = makeEonReply(c.getNickName(), channels_name[i]);

			if (ChIt != tempCh.end())
			{
				if (s.getChannel(channels_name[i])->getPassword() != key)
				{
					reply(fd, 475, channels_name[i]);
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
			std::cout << "msg : [" << msg <<  "]" << std::endl;
			broadcast(tempCh, channels_name[i], msg);
			nameReply = attachClientList(tempCh, channels_name[i], nameReply);
			reply(fd, 353, nameReply);
			reply(fd, 366, eonReply);
			if (keyIter < channels_passwd.end())
				keyIter++;
		}
    }
}