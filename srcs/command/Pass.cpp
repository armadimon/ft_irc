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
			// ERR_NEEDMOREPARAMS 461
			reply(fd, 461, c.getNickName(), cmd.getCmd());
			return;
		}
		for (; it < cmd.getParams().end(); it++)
		{		
			std::cout << "server_pass : [" << cmd.getServer().getPass() << std::endl;
			std::cout << "input_pass : [" << *it << std::endl;

			if (cmd.getServer().getPass() == *it)
				c.setUserState(PWSET);
			std::cout << "State : " << c.getUserState() << std::endl;
		}
	}
	else if (c.getUserState() == REGISTER)
	{
		// ERR_ALREADYREGISTRED 462
		reply(fd, 462, c.getNickName(), cmd.getCmd());
		return;
	}
}