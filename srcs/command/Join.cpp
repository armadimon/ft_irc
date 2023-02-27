#include "../../includes/Command.hpp"

static std::string makeNameReply(std::string nickName, std::string chName, std::string chMode)
{
	std::string str = "";

	str += nickName;
	str += " ";
	str += chMode;
	str += " ";
	str += chName;
	str += " ";
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

static std::string makeEonReply(std::string nickName, std::string chName)
{
	std::string str = "";

	str += nickName;
	str += " ";
	str += chName;
	str += " ";
	return (str);
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
		// 요청한 클라이언트의 정보를 가져와서 prefix 조합
		std::string	prefix = ":";
		prefix += c.getNickName();
		prefix += "!";
		prefix += c.getUserName();
		prefix += "@";
		prefix += c.getHostName();
		prefix += " ";

		std::vector<std::string>::iterator keyIter = channels_passwd.begin();
		for (size_t i = 0; i < channels_name.size(); i++)
		{
			std::string key = keyIter < channels_passwd.end() ? *keyIter++ : "";
			// 서버에 채널이 생성되어 있는지 확인
			std::map<std::string, Channel *> &tempCh = s.getChannels();
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);

			// make reply for each channel
			std::string nameReply = makeNameReply(c.getNickName(), channels_name[i], "=");
			std::string eonReply = makeEonReply(c.getNickName(), channels_name[i]);

			if (ChIt != tempCh.end())
			{
				std::cout << "input : " << key << std::endl;
				std::cout << "password : " << s.getChannel(channels_name[i])->getPassword() << std::endl;
				if (s.getChannel(channels_name[i])->getPassword() != key)
				{
					reply(fd, 475, channels_name[i]);
					continue;
				}
				s.getChannels()[channels_name[i]]->addClient(fd, c.getNickName());
				c.addmyChannelList(channels_name[i]);
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
			std::string msg = "";
			msg += prefix;
			msg += "JOIN :";
			msg += channels_name[i];
			msg += "\r\n";
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