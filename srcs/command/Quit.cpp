#include "../../includes/Command.hpp"

// QUIT [<Quit message>]
void	cmdQuit(Command cmd, int fd)
{
	std::string message = "";
	if (cmd.getTrailing().size() > 1)
	{
		std::cout << "trailing?" << std::endl;
		message = cmd.getTrailing();
	}
	else if (cmd.getParams().size() > 0)
		message = cmd.getParams()[0];

	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);
	std::cout << "client addr : " << &c << std::endl;
	std::cout << "c fd : " << fd << std::endl;

	// 서버에 메시지 보내기
	std::cout << "quit" << std::endl;
	c.setMsgBuf(c.getMsgBuf() + "ERROR :Closing link: (" + c.getNickName() + "@" + c.getHostName() + ")[Quit: " + message + "]\r\n");
	std::cout << c.getMsgBuf() << std::endl;
	c.setUserState(LOGOFF);
}