#include "../../includes/Command.hpp"

// KICK <channel> <user> [<comment>]
void	cmdKick(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	std::string comment;
	if (params.size() == 3)	comment = params[2];
	else if (!cmd.getTrailing().empty()) comment = cmd.getTrailing();

	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);
	std::string channel_name;
	std::vector<std::string> tmp_users;
	std::vector<std::string> user_names;

	if (c.getUserState() == REGISTER)
	{
		if (params.size() < 2)
		{
			c.setSendBuf(reply(461, c.getNickName(), cmd.getCmd()));
			return;
		}
		channel_name = params[0];
		if (channel_name.size() > 50)
		{
			c.setSendBuf(reply(476, c.getNickName(), channel_name));   // ERR_BADCHANMASK 476
			return;
		}

		// 채널이 존재하는지 검사
		if (!cmd.getServer().isExistChannel(channel_name))
		{
			// ERR_NOSUCHCHANNEL
			c.setSendBuf(reply(403, c.getNickName(), channel_name));
			return;
		}
		Channel *chan = cmd.getServer().getChannel(channel_name);
		// 요청한 클라이언트가 실제 채널 operator인지 확인
		if (fd != chan->getOperatorFD())
		{
			// ERR_CHANOPRIVSNEEDED
			c.setSendBuf(reply(482, c.getNickName(), channel_name));
			return;
		}

		if (!chan->isExistClient(c.getNickName()))
		{
			c.setSendBuf(reply(442, c.getNickName(), channel_name));
			return;
		}

		tmp_users = string_split(params[1], ",");
		for (size_t i = 0; i < tmp_users.size(); i++)
		{
			// 유저가 없으면 ERR_NOTONCHANNEL
			if (!chan->isExistClient(tmp_users[i]))
				c.setSendBuf(reply(441, c.getNickName(), tmp_users[i] + " " + channel_name));
			else
				user_names.push_back(tmp_users[i]);
		}

		std::vector<std::string>::iterator it = user_names.begin();
		for (; it != user_names.end(); it++)
		{
			Client& client = cmd.getServer().getClient(*it);
			std::string	prefix = makePrefix(c);

			std::string msg = "";
			msg += prefix;
			msg += "KICK ";
			msg += channel_name;
			if (comment.size() > 0)
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
			broadcast(cmd.getServer().getChannels(), channel_name, msg, s);
	
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			client.removeChannelFromList(channel_name);
			// 해당 클라이언트를 채널 리스트에서 삭제
			cmd.getServer().removeClientFromChannel(chan, client.getFD());
		}
	}
}