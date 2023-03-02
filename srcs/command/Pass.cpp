#include "../../includes/Command.hpp"

void	cmdPass(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();

	Client &c = cmd.getServer().getClient(fd);

	std::vector<std::string>::iterator it = cmd.getParams().begin();
	if (c.getUserState() == DEFAULT || c.getUserState() == PWSET)
	{
		if (params.size() < 1)
		{
			c.setSendBuf(reply(461, c.getNickName(), cmd.getCmd()));
			return;
		}
		for (; it < cmd.getParams().end(); it++)
		{		
			if (cmd.getServer().getPass() == *it)
				c.setUserState(PWSET);
		}
	}
	else if (c.getUserState() == REGISTER)
	{
		// ERR_ALREADYREGISTRED 462
		c.setSendBuf(reply(462, c.getNickName(), cmd.getCmd()));
		return;
	}
}