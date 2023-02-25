#include "../../includes/Command.hpp"

void	cmdNick(Command cmd, int fd)
{
	// if (str.size() < 1) // ERR_NONICKNAMEGIVEN 431
	std::vector<std::string> params = cmd.getParams();
	Client &c = cmd.getServer().getClient(fd);

	if (c.getUserState() == REGISTER)
	{
		c.setNickName(params[0]);
	}
	std::cout << "nick cmd : " << c.getNickName() << std::endl;
}