#include "../includes/Command.hpp"

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

void	cmdPass(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);

	int cnt = 0;

	if (c->getUserState() == DEFAULT)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
			{
				int endPos = it->find_last_not_of("\n\r");
				
				std::cout << "server_pass : [" << s->getPass() << std::endl;
				std::cout << "input_pass : [" << it->substr(0, endPos + 1) << std::endl;

				if (s->getPass() == it->substr(0, endPos +1))
					c->setUserState();
				std::cout << "State : " << c->getUserState() << std::endl;
				// std::string temp;
				// temp = 
				// if (s->getPass() == *it)
			}
			cnt++;
		}
	}
}

void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);

	std::string temp = ":";
	std::vector<int> reciver;

	int cnt = 0;
	if (c->getUserState() == REGISTER)
	{
		temp += c->getNickName();
		temp += "!";
		temp += c->getUserName();
		temp += "@";
		temp += c->getHostName();
		temp += " ";
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
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
			temp += *it;
			if (cnt != 2)
				temp += " ";
			cnt++;
		}
		std::vector<int>::iterator vecIter = reciver.begin();
		for (; vecIter < reciver.end(); vecIter++)
		{
			std::cout << "vec iter : " << *vecIter << std::endl;
			send(*vecIter, temp.c_str(), temp.size(), 0);
		}
	}
}

void	cmdUser(Server *s, int fd, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);
	int cnt = 0;

	if (c->getUserState() == REGISTER)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
				c->setUserName(*it);
			else if (cnt == 2)
				c->setHostName(*it);
			else if (cnt == 3)
				;
			else if (cnt == 4)
				c->setRealName(*it);
			cnt++;
		}
		std::cout << "User cmd : " << c->getUserName() << std::endl;
		std::cout << "User cmd : " << c->getHostName() << std::endl;
		std::cout << "User cmd : " << c->getRealName() << std::endl;
	}
}

void cmdJoin(Server* s, int fd, std::vector<std::string> str)
{
    std::vector<std::string>::iterator it = str.begin();
    Client* c = s->getClient(fd);
    int cnt = 0;
	std::vector<std::string> channels_name;
	std::vector<std::string> channels_passwd;

    if (c->getUserState() == REGISTER)
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
		std::vector<std::string>::iterator nameIter = channels_name.end() - 1;

		int endPos = it->find_last_not_of("\n\r");
		*nameIter = nameIter->substr(0, endPos +1);
		std::cout << channels_name.size() << std::endl;
		for (size_t i = 0; i < channels_name.size(); i++)
		{
			// 서버에 채널이 생성되어 있는지 확인
			std::map<std::string, Channel *> tempCh = s->getChannel();
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);
			if (channels_passwd.size() > 0 && channels_passwd[i] != (*ChIt).second->getPassword())
			{
				// numeric reply 날리기 ERR_BADCHANNELKEY
			}
			if (ChIt != tempCh.end())
			{
				// 채널이 존재하는 플래그
				// 이미 서버가 있는 상태
				(*ChIt).second->addClient(fd, c);
				c->addmyChannelList((*ChIt).second->getChannelName());
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			else
			{
				// 새로 서버 만들기
				tempCh.insert(std::pair<std::string, Channel *>(channels_name[i], new Channel(channels_name[i], fd)));
				c->addmyChannelList(channels_name[i]);
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}

			std::string nameReply = "353 ";
			std::string eonReply = "363 ";
			nameReply += tempCh[channels_name[0]]->getChannelName();
			eonReply += tempCh[channels_name[0]]->getChannelName();
			nameReply += " :";
			eonReply += " :End of NAMES list\r\n";
			std::map<int, Client *> tempClient = s->getClients();

			std::string	prefix = ":";
			prefix += c->getNickName();
			prefix += "!";
			prefix += c->getUserName();
			prefix += "@";
			prefix += c->getHostName();
			prefix += " ";

			std::vector<std::string>::iterator msgIter = str.begin();
			while (msgIter < str.end())
			{
				prefix += *msgIter;
				msgIter++;
				if (msgIter != str.end())
					prefix += " ";
			}
			std::map<int, Client *>::iterator clientIter = tempClient.begin();
			for (;clientIter != tempClient.end(); clientIter++)
			{
				std::string cname = clientIter->second->getNickName();
				nameReply += cname;
				nameReply += " ";
			}
			nameReply += "\r\n";
			clientIter =tempClient.begin();
			for (;clientIter != tempClient.end(); clientIter++)
			{
				int	cFd = clientIter->second->getFD();
				// nickname, username, hostname;
				std::cout << prefix << std::endl;
				send(cFd, prefix.c_str(), prefix.size(), 0);
				// 요청한 클라이언트에게만 reply
				if (cFd == fd)
					send(cFd, nameReply.c_str(), nameReply.size(), 0);
				send(cFd, eonReply.c_str(), eonReply.size(), 0);
			}
		}
    }
}