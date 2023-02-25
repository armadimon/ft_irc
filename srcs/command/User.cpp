#include "../../includes/Command.hpp"

void	cmdUser(Command cmd, int fd)
{
	// if (str.size() < 4) // ERR_NEEDMOREPARAMS 461
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);

	// ERR_ALREADYREGISTRED 462 = username, hostname, realname 전부 저장되있을 때
	if (c.getUserState() == REGISTER)
	{
		c.setUserName(params[0]);
		c.setHostName(params[1]);
		c.setRealName(params[3]);
		std::cout << "User cmd : " << c.getUserName() << std::endl;
		std::cout << "User cmd : " << c.getHostName() << std::endl;
		std::cout << "User cmd : " << c.getRealName() << std::endl;
	}
}