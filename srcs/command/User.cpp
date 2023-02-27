#include "../../includes/Command.hpp"

void	cmdUser(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	if (params.size() < 4)
	{
		// ERR_NEEDMOREPARAMS
		reply(fd, 461, cmd.getCmd());
		return;
	}
	
	Client &c = cmd.getServer().getClient(fd);
	// ERR_ALREADYREGISTRED 462 = username, hostname, realname 전부 저장되있을 때
	if (c.getUserState() == PWSET || c.getUserState() == READY)
	{
		c.setUserName(params[0]);
		c.setHostName(params[1]);
		if (cmd.getTrailing().size() > 0)
			c.setRealName(cmd.getTrailing());
		else if (params[3].size() > 0)
			c.setRealName(params[3]);
		std::cout << "User cmd : " << c.getUserName() << std::endl;
		std::cout << "User cmd : " << c.getHostName() << std::endl;
		std::cout << "User cmd : " << c.getRealName() << std::endl;
		c.setUserState(READY);
	}
	else if (c.getUserState() == REGISTER)
	{
		reply(fd, 462, 0);
	}
}