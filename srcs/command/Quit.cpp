#include "../../includes/Command.hpp"

void	cmdQuit(Command cmd, int fd)
{
	std::string message = "";
	if (cmd.getTrailing().size() > 1)
		message = cmd.getTrailing();
	else if (cmd.getParams().size() > 0)
		message = cmd.getParams()[0];

	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	c.setSendBuf(c.getSendBuf() + "ERROR :Closing link: (" + c.getNickName() + "@" + c.getHostName() + ")[Quit: " + message + "]\r\n");
	c.setUserState(LOGOFF);
}