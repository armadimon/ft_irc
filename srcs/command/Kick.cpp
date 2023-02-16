#include "../../includes/Command.hpp"

// KICK <channel> <user> [<comment>]
void	cmdKick(Server* s, int fd, std::vector<std::string> str)
{
	// if (str.size() < 4) ERR_NEEDMOREPARAMS
	std::vector<std::string>::iterator it = str.begin();
	Client *c = s->getClient(fd);
	int cnt = 0;
	std::vector<std::string> channel_names;
	std::vector<std::string> user_names;
	std::string comment;

	if (c->getUserState() == REGISTER)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
			{
				channel_names = string_split(*it, ",");
				// 채널이 존재하는지 검사
				std::vector<std::string>::iterator chit = channel_names.begin();
				for (; chit < channel_names.end(); chit++)
				{
					if (!s->isExistChannel(*chit))
						channel_names.erase(chit);
				}
			}
			else if (cnt == 2)
			{
				user_names = string_split(*it, ",");
				// 유저가 존재하지 않는 경우 처리 나중에 생각.
			}
			else if (cnt == 3)
			{
				comment = *it;
			}
			cnt++;
		}

		std::vector<std::string>::iterator iter = channel_names.begin();
		for (; iter > channel_names.end(); iter++)
		{
			// 요청한 클라이언트가 실제 채널 operator인지 확인
			if (c->getFD() != s->getChannel().find(*iter)->second->getOperatorFD())
				continue;
			// 해당 클라이언트를 채널 리스트에서 삭제
			s->getChannel().find(*iter)->second->removeClient(fd);
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			c->removeChannelFromList(*iter);
			// TODO : 해당 클라이언트가 자기 자신=operator일 경우 채널 삭제.
		}

	}
}