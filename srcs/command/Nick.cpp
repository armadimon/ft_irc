#include "../../includes/Command.hpp"

void	cmdNick(Command cmd, int fd)
{
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);

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
	if (c.getUserState() == REGISTER)
	{
		c.setNickName(params[0]);
	}
	std::cout << "nick cmd : " << c.getNickName() << std::endl;
}