#include "../../includes/Command.hpp"

// KICK <channel> <user> [<comment>]
void	cmdKick(Command cmd, int fd)
{
<<<<<<< HEAD
	std::vector<std::string> params = cmd.getParams();
	if (params.size() < 2)
	{
		reply(fd, 461, cmd.getCmd());
		return;
	}

	Client &c = cmd.getServer().getClient(fd);
=======
	if (str.size() < 3)
	{
		reply(fd, 461, str[0]);
		return;
	}
	std::vector<std::string>::iterator it = str.begin(); // KICK
	Client &c = s->getClient(fd);
	int cnt = 0;
>>>>>>> 68bf89ef39c49ec3f6b2aaf196af374d802d2592
	std::string channel_name;
	std::vector<std::string> user_names;
	std::string comment;

	if (c.getUserState() == REGISTER)
	{
		channel_name = params[0];
		// 채널이 존재하는지 검사
		if (!cmd.getServer().isExistChannel(channel_name))
		{
<<<<<<< HEAD
			// ERR_NOSUCHCHANNEL
			reply(fd, 403, channel_name);
			return;
		}
		Channel *chan = cmd.getServer().getChannel(channel_name);
		user_names = string_split(params[1], ",");
		comment = params[2];
=======
			if (cnt == 1)
			{
				channel_name = *it;
				// 채널이 존재하는지 검사
				if (!s->isExistChannel(channel_name))
				{
					// ERR_NOSUCHCHANNEL
					reply(fd, 403, channel_name);
					return;
				}
			}
			else if (cnt == 2)
				user_names = string_split(*it, ",");
			else if (cnt == 3)
				comment = *it;
			cnt++;
		}
		Channel* chan = s->getChannel(channel_name);
>>>>>>> 68bf89ef39c49ec3f6b2aaf196af374d802d2592
		// 요청한 클라이언트가 실제 채널 operator인지 확인
		if (fd != chan->getOperatorFD())
		{
			// ERR_CHANOPRIVSNEEDED
			reply(fd, 482, channel_name);
			return;
		}
<<<<<<< HEAD

		std::vector<std::string>::iterator it = user_names.begin();
		for (; it != user_names.end(); it++)
		{
			// 유저가 없으면 ERR_NOTONCHANNEL
			if (!chan->isExistClient(*it))
			{
				reply(fd, 442, channel_name);
				return;
=======
		std::vector<std::string>::iterator userit = user_names.begin();
		std::cout << channel_name << std::endl;
		for (; userit != user_names.end(); userit++)
		{
			Client& client = s->getClient(*userit);
			// 유저가 없으면 ERR_NOTONCHANNEL
			if (!chan->isExistClient(*userit))
			{
				reply(fd, 442, channel_name);
				continue;
>>>>>>> 68bf89ef39c49ec3f6b2aaf196af374d802d2592
			}

			Client& client = cmd.getServer().getClient(*it);
			std::string	prefix = ":";
			prefix += c.getNickName();
			prefix += "!";
			prefix += c.getUserName();
			prefix += "@";
			prefix += c.getHostName();
			prefix += " ";

			std::string msg = "";
			msg += prefix;
			msg += "KICK ";
			msg += channel_name;
			if (params.size() == 3)
			{
				msg += " ";
				msg += *it;
				msg += " ";
				msg += comment;
			}
			else
			{
				msg += " :";
				msg += *it;
			}
			msg += "\r\n";
			broadcast(cmd.getServer().getChannels(), channel_name, msg);

			// 해당 클라이언트를 채널 리스트에서 삭제
			chan->removeClient(client.getFD());
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			client.removeChannelFromList(channel_name);
			// 삭제하려는 클라이언트가 operator여도 그대로 삭제함! 채널은 남아있음.
		}
		// 채널에 해당 유저가 채널에서 kick당했다고 날리기
	}
}