#include "../../includes/Command.hpp"

// PART <channel>{,<channel>}
void	cmdPart(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	std::string comment;

	if (params.size() < 1)
	{
		reply(fd, 461, cmd.getCmd());
		return;
	}
	if (params.size() == 2)	comment = params[1];
	else if (!cmd.getTrailing().empty()) comment = cmd.getTrailing();

	Client &c = cmd.getServer().getClient(fd);
	std::vector<std::string> tmp_channels;
	std::vector<std::string> channel_names;

	if (c.getUserState() == REGISTER)
	{
		tmp_channels = string_split(params[0], ",");
		for (size_t i = 0; i < tmp_channels.size(); i++)
		{
			if (!cmd.getServer().isExistChannel(tmp_channels[i]))
				reply(fd, 403, tmp_channels[i]);  // ERR_NOSUCHCHANNEL
			else
				channel_names.push_back(tmp_channels[i]);
		}

		std::vector<std::string>::iterator it = channel_names.begin();
		for (; it < channel_names.end(); it++)
		{
			Channel *chan = cmd.getServer().getChannel(*it);

			if (!chan->isExistClient(c.getNickName()))
			{
				reply(fd, 442, *it);
				continue;
			}
			
			std::string	prefix = ":";
			prefix += c.getNickName();
			prefix += "!";
			prefix += c.getUserName();
			prefix += "@";
			prefix += c.getHostName();
			prefix += " ";

			std::string msg = "";
			msg += prefix;
			msg += "PART ";
			// msg += channel_name;
			if (comment.size() > 0)
			{
				msg += (*it);
				msg += " ";
				msg += comment;
			}
			else
				msg += (*it);
			msg += "\r\n";
			broadcast(cmd.getServer().getChannels(), *it, msg);
			chan->removeClient(c.getFD());
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			c.removeChannelFromList(*it);		
		}
	}
}