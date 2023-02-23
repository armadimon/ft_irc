#include "../../includes/Command.hpp"

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
			
			std::cout << "[" << channels_name[i] << "]" << std::endl;
			// 서버에 채널이 생성되어 있는지 확인
			std::map<std::string, Channel *> tempCh = s->getChannel();
			std::cout << "size : " << tempCh.size() << std::endl;
			// std::cout << "ch name : [" << tempCh.begin()->second->getChannelName() <<"]" << std::endl;
			std::map<std::string, Channel *>::iterator ChIt = tempCh.find(channels_name[i]);
			// std::cout << "ch name : [" << ChIt->second->getChannelName() <<"]" << std::endl;


			std::string nameReply = "";
			std::string eonReply = "";
			nameReply += "juahn = ";
			eonReply += "juahn ";
			nameReply += channels_name[i];
			eonReply += channels_name[i];
			nameReply += " :";


			if (channels_passwd.size() > 0 && channels_passwd[i] != (*ChIt).second->getPassword())
			{
				// numeric reply 날리기 ERR_BADCHANNELKEY
			}
			if (ChIt != tempCh.end())
			{
			std::cout << "JOIN check 1" << std::endl;
				// 채널이 존재하는 플래그
				// 이미 채널이 있는 상태
				s->getChannel()[trim(channels_name[i], "#")]->addClient(fd, c.getNickName());
				c.addmyChannelList(trim(channels_name[i], "#"));
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			else
			{
			std::cout << "JOIN check 2" << std::endl;
				// 새로 채널 만들기
				s->setChannel(trim(channels_name[i], "#"), fd);
				s->getChannel()[trim(channels_name[i], "#")]->addClient(fd, c.getNickName());
				c.addmyChannelList(trim(channels_name[i], "#"));
				// send(fd, prefix.c_str(), prefix.size(), 0);
				// send(cFd, eonReply.c_str(), eonReply.size(), 0);
				// 해당 클라이언트가 join했다고 채널에 메세지 날리기
			}
			tempCh = s->getChannel();

			std::map<int, std::string> tempClient = tempCh[channels_name[0]]->getClientList();
			// std::map<int, Client *> tempClient = s->getClients();
			std::cout << "cli size : " << tempClient.size() << std::endl;
			// 수정필요. 
			std::map<int, std::string>::iterator clientIter = tempClient.begin();
			for (;clientIter != tempClient.end();)
			{
				std::string cname = clientIter->second;
				if (s->getChannel()[channels_name[0]]->getOperatorFD() == clientIter->first)
					nameReply += "@";
				nameReply += cname;
				clientIter++;
				if (clientIter != tempClient.end())
					nameReply += " ";
			}
			nameReply += "\r\n";
			clientIter =tempClient.begin();
			for (;clientIter != tempClient.end(); clientIter++)
			{
				int	cFd = clientIter->first;
				// nickname, username, hostname;
				std::cout << prefix << std::endl;
				send(cFd, prefix.c_str(), prefix.size(), 0);
				// 요청한 클라이언트에게만 reply
			}
			reply(fd, 353, nameReply);
			reply(fd, 366, eonReply);
		}
    }
}