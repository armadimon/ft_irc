#include "../../includes/Command.hpp"

void	cmdNick(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	if (params.size() < 1) 
	{
		c.setSendBuf(reply(431, c.getNickName(), ""));
		return;
	}
	if (params[0].size() > 9)
	{
		c.setSendBuf(reply(432, c.getNickName(), params[0]));
		return;
	}
	if (cmd.getServer().isAlreadyUsed(params[0]))
	{
		c.setSendBuf(reply(433, c.getNickName(), params[0]));
		return;
	}
	if (c.getUserState() == PWSET || c.getUserState() == READY)
	{
		c.setNickName(params[0]);
		c.setUserState(READY);
	}
	else if (c.getUserState() == REGISTER)
	{

		if (s.isAlreadyUsed(params[0]))
		{
			c.setSendBuf(reply(436, c.getNickName(), params[0]));
		}
		else
		{
			std::string str = makePrefix(c) + cmd.getCmd() + " " + params[0] + "\r\n";
			c.setNickName(params[0]);
			c.setSendBuf(str);
		}
	}
}