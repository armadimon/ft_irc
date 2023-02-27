#include "../../includes/Command.hpp"

void	cmdNick(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	if (params.size() < 1) 
	{
		reply(fd, 431, NULL);
		return;
	}
	if (params[0].size() > 9)
	{
		reply(fd, 432, params[0]);
		return;
	}
	if (cmd.getServer().isAlreadyUsed(params[0]))
	{
		reply(fd, 433, params[0]);
		return;
	}
	if (c.getUserState() == PWSET)
	{
		c.setNickName(params[0]);
		c.setUserState(READY);
	}
	else if (c.getUserState() == REGISTER)
	{

		if (s.isAlreadyUsed(params[0]))
		{
			reply(fd, 436, params[0]);
		}
		else
		{
			std::string str = makePrefix(c) + cmd.getCmd() + " " + params[0] + "\r\n";
			c.setNickName(params[0]);
			send(fd, str.c_str(), str.size(), 0);
		}
	}
	std::cout << "nick cmd : " << c.getNickName() << std::endl;
}