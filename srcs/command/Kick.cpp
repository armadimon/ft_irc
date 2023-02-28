#include "../../includes/Command.hpp"

// KICK <channel> <user> [<comment>]
void	cmdKick(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	std::string comment;

	if (params.size() < 2)
	{
		reply(fd, 461, cmd.getCmd());
		return;
	}
	if (params.size() == 3)	comment = params[2];
	else if (!cmd.getTrailing().empty()) comment = cmd.getTrailing();

	Client &c = cmd.getServer().getClient(fd);
	std::string channel_name;
	std::vector<std::string> tmp_users;
	std::vector<std::string> user_names;

	if (c.getUserState() == REGISTER)
	{
		channel_name = params[0];
		if (channel_name.size() > 50)
		{
			reply(fd, 476, channel_name);   // ERR_BADCHANMASK 476
			return;
		}

		// 채널이 존재하는지 검사
		if (!cmd.getServer().isExistChannel(channel_name))
		{
			// ERR_NOSUCHCHANNEL
			reply(fd, 403, channel_name);
			return;
		}
		Channel *chan = cmd.getServer().getChannel(channel_name);
		// 요청한 클라이언트가 실제 채널 operator인지 확인
		if (fd != chan->getOperatorFD())
		{
			// ERR_CHANOPRIVSNEEDED
			reply(fd, 482, channel_name);
			return;
		}

		if (!chan->isExistClient(c.getNickName()))
		{
			reply(fd, 442, channel_name);
			return;
		}

		tmp_users = string_split(params[1], ",");
		for (size_t i = 0; i < tmp_users.size(); i++)
		{
			// 유저가 없으면 ERR_NOTONCHANNEL
			if (!chan->isExistClient(tmp_users[i]))
				reply(fd, 441, tmp_users[i] + " " + tmp_users[i] + " " + channel_name);
			else
				user_names.push_back(tmp_users[i]);
		}

		std::vector<std::string>::iterator it = user_names.begin();
		for (; it != user_names.end(); it++)
		{
			std::cout << "user : " << *it << std::endl;
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
			std::cout << msg << std::endl;
			broadcast(cmd.getServer().getChannels(), channel_name, msg);
	
			std::map<int, std::string> clientlist = chan->getClientList();
			std::map<int, std::string>::iterator clist_it = clientlist.begin();
			std::cout << "[before client list]" << std::endl;
			for (; clist_it != clientlist.end(); clist_it++)
				std::cout << (*clist_it).second << std::endl;
			// 해당 클라이언트를 채널 리스트에서 삭제
			chan->removeClient(client.getFD());
			std::map<int, std::string> clientlist2 = chan->getClientList();
			std::map<int, std::string>::iterator clist_it2 = clientlist2.begin();
			std::cout << "[after client list]" << std::endl;
			for (; clist_it2 != clientlist2.end(); clist_it2++)
				std::cout << (*clist_it2).second << std::endl;

			std::vector<std::string> chanlist = c.getmyChannelList();
			std::vector<std::string>::iterator list_it = chanlist.begin();
			std::cout << "[before channel list]" << std::endl;
			for (; list_it < chanlist.end(); list_it++)
				std::cout << *list_it << std::endl;
			// 클라이언트의 myChannelList에서 해당 채널을 삭제.
			client.removeChannelFromList(channel_name);
			std::vector<std::string> chanlist2 = c.getmyChannelList();
			std::vector<std::string>::iterator list_it2 = chanlist2.begin();
			std::cout << "[after channel list]" << std::endl;
			for (; list_it2 < chanlist2.end(); list_it2++)
				std::cout << *list_it2 << std::endl;

			// 삭제하려는 클라이언트가 operator여도 그대로 삭제함! 채널은 남아있음.
		}
		// 채널에 해당 유저가 채널에서 kick당했다고 날리기
	}
}