#include "../../includes/Command.hpp"

// QUIT [<Quit message>]
void	cmdQuit(Command cmd, int fd)
{
	std::string message = "";
	if (cmd.getTrailing().size() > 1)
		message = cmd.getTrailing();
	else if (cmd.getParams().size() > 0)
		message = cmd.getParams()[0];

	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	// 서버에 메시지 보내기
	c.setSendBuf(c.getSendBuf() + "ERROR :Closing link: (" + c.getNickName() + "@" + c.getHostName() + ")[Quit: " + message + "]\r\n");
	c.setUserState(LOGOFF);
}