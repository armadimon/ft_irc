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

static void sendJoinMsg(std::map<std::string, Channel *> tempCh, std::string chName, std::string prefix)
{
	std::map<int, std::string> tempClient = tempCh[chName]->getClientList();
	std::map<int, std::string>::iterator clientIter = tempClient.begin();
	clientIter = tempClient.begin();
	for (;clientIter != tempClient.end(); clientIter++)
	{
		int	cFd = clientIter->first;
		send(cFd, prefix.c_str(), prefix.size(), 0);
		// 요청한 클라이언트에게만 reply
	} 
}

static std::string attachClientList(std::map<std::string, Channel *> tempCh, std::string chName, std::string nameReply)
{
	std::map<int, std::string> tempClient = tempCh[chName]->getClientList();
	std::map<int, std::string>::iterator clientIter = tempClient.begin();
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

void cmdJoin(Server* s, int fd, std::vector<std::string> str)
{
    std::vector<std::string>::iterator it = str.begin();
    Client &c = s->getClient(fd);
    int cnt = 0;
	std::vector<std::string> channels_name;
	std::vector<std::string> channels_passwd;

    if (c.getUserState() == REGISTER)
    {
        for (; it < str.end(); it++)
        {
			std::cout << *it << std::endl;
            if (cnt == 1)
				channels_name = string_split(*it, ",");
			else if (cnt == 2)
				channels_passwd = string_split(*it, ",");
			cnt++;
        }

		// 요청한 클라이언트의 정보를 가져와서 prefix 조합
		std::string	prefix = ":";
		prefix += c.getNickName();
		prefix += "!";
		prefix += c.getUserName();
		prefix += "@";
		prefix += c.getHostName();
		prefix += " ";

		// 조합한 prefix와 받은 msg 전체를 재조립
		std::vector<std::string>::iterator msgIter = str.begin();
		while (msgIter < str.end())
		{
			if ((*msgIter).find("#") != std::string::npos)
				prefix += ":";
			prefix += *msgIter;
			msgIter++;
			if (msgIter != str.end())
				prefix += " ";
		}

		std::vector<std::string>::iterator nameIter = channels_name.end() - 1;

		size_t endPos = nameIter->find_last_not_of("\n\r");
		if (endPos != std::string::npos)
			*nameIter = nameIter->substr(0, endPos +1);
		std::cout << channels_name.size() << std::endl;
		for (size_t i = 0; i < channels_name.size(); i++)
		{
			
			// 서버에 채널이 생성되어 있는지 확인
			std::map<std::string, Channel *> tempCh = s->getChannels();
			// std::cout << "ch name : [" << tempCh.begin()->second->getChannelName() <<"]" << std::endl;
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);
			// std::cout << "ch name : [" << ChIt->second->getChannelName() <<"]" << std::endl;

			// make reply for each channel
			std::string nameReply = makeNameReply(c.getNickName(), channels_name[i], "=");
			std::string eonReply = makeEonReply(c.getNickName(), channels_name[i]);


			if (channels_passwd.size() > 0 && channels_passwd[i] != (*ChIt).second->getPassword())
			{
				// numeric reply 날리기 ERR_BADCHANNELKEY
			}
			if (ChIt != tempCh.end())
			{
				s->getChannels()[channels_name[i]]->addClient(fd, c.getNickName());
				c.addmyChannelList(channels_name[i]);
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			else
			{
				// 새로 채널 만들기
				s->setChannel(channels_name[i], fd);
				s->getChannels()[channels_name[i]]->addClient(fd, c.getNickName());
				c.addmyChannelList(channels_name[i]);
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			sendJoinMsg(tempCh, channels_name[i], prefix);
			nameReply = attachClientList(tempCh, channels_name[i], nameReply);
			reply(fd, 353, nameReply);
			reply(fd, 366, eonReply);
		}
    }
}