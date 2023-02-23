#include "../../includes/Command.hpp"

// KICK <channel> <user> [<comment>]
void	cmdKick(Server* s, int fd, std::vector<std::string> str)
{
	// if (str.size() < 4) ERR_NEEDMOREPARAMS
	std::vector<std::string>::iterator it = str.begin();
	Client &c = s->getClient(fd);
	int cnt = 0;
	std::string channel_name;
	std::vector<std::string> user_names;
	std::string comment;

	if (c.getUserState() == REGISTER)
	{
		for (; it < str.end(); it++)
		{
			if (cnt == 1)
			{
				channel_name = *it;
				// 채널이 존재하는지 검사
				if (!s->isExistChannel(channel_name))
				{
					// ERR_NOSUCHCHANNEL
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
		// 요청한 클라이언트가 실제 채널 operator인지 확인
		// if (fd != s->findChannel(channel_name)->getOperatorFD())
		// {
		// 	// ERR_CHANOPRIVSNEEDED
		// 	exit(1);
		// }
		std::vector<std::string>::iterator userit = user_names.begin();
		for (; userit != user_names.end(); userit++)
		{
			// 해당 클라이언트를 채널 리스트에서 삭제
			// s->findChannel(channel_name)->removeClient(*userit);
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			s->getClient(*userit).removeChannelFromList(channel_name);
			// 삭제하려는 클라이언트가 operator여도 그대로 삭제함! 채널은 남아있음.
		}
	}
}