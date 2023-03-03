#include "../../includes/Command.hpp"

// USER <username> <hostname> <servername> <realname>
void	cmdUser(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);
	if (c.getUserState() == PWSET || c.getUserState() == READY)
	{
		if (params.size() + cmd.getTrailing().size() < 4)
		{
			c.setSendBuf(reply(461, c.getNickName(), cmd.getCmd()));
			return;
		}
		c.setUserName(params[0]);
		if (cmd.getTrailing().size() > 0)
			c.setRealName(cmd.getTrailing());
		else if (params[3].size() > 0)
			c.setRealName(params[3]);
		c.setUserState(READY);
	}
	else if (c.getUserState() == REGISTER)
	{
		c.setSendBuf(reply(462, c.getNickName(), cmd.getCmd()));
	}
}