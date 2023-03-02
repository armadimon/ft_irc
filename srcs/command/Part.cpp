#include "../../includes/Command.hpp"

// PART <channel>{,<channel>}
void	cmdPart(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	std::string comment;
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);
	std::vector<std::string> tmp_channels;
	std::vector<std::string> channel_names;

	if (c.getUserState() == REGISTER)
	{
		if (params.size() < 1)
		{
			c.setSendBuf(reply(461, c.getNickName(), cmd.getCmd()));
			return;
		}
		if (params.size() == 2)	comment = params[1];
		else if (!cmd.getTrailing().empty()) comment = cmd.getTrailing();
		tmp_channels = string_split(params[0], ",");
		for (size_t i = 0; i < tmp_channels.size(); i++)
		{
			if (!s.isExistChannel(tmp_channels[i]))
				c.setSendBuf(reply(403, c.getNickName(), tmp_channels[i]));  // ERR_NOSUCHCHANNEL
			else
				channel_names.push_back(tmp_channels[i]);
		}

		std::vector<std::string>::iterator it = channel_names.begin();
		for (; it < channel_names.end(); it++)
		{
			Channel *chan = s.getChannel(*it);

			if (!chan->isExistClient(c.getNickName()))
			{
				c.setSendBuf(reply(442, c.getNickName(), *it));
				continue;
			}
			
			std::string	prefix = makePrefix(c);
			std::string msg = "";
			msg += prefix + "PART ";
			// msg += channel_name;
			if (comment.size() > 0)
				msg += (*it) + " " + comment;
			else
				msg += (*it);
			msg += "\r\n";
			broadcast(s.getChannels(), *it, msg, s);
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			c.removeChannelFromList(*it);		
			s.removeClientFromChannel(chan, c.getFD());
		}
	}
}