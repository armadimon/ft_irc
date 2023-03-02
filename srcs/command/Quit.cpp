#include "../../includes/Command.hpp"

// QUIT [<Quit message>]
void	cmdQuit(Command cmd, int fd)
{
	std::string message;
	if (cmd.getTrailing().size() > 0)
		message = cmd.getTrailing();
	else if (cmd.getParams().size() > 0)
		message = cmd.getParams()[0];

	Server &s = cmd.getServer();
	Client &c = s.getClient(fd);

	// 서버에 메시지 보내기
	std::cout << "quit" << std::endl;
	c.msg += "ERROR :Closing link: (" + c.getNickName() + ")[Client exited]\r\n";
	std::cout << "address : " << &c.msg << std::endl;
	std::cout << "size : " << c.msg.size() << std::endl;
	//send(fd, c.msg.c_str(), c.msg.size(), 0);
	// 채널에 메시지 보내기
	// 해당 클라이언트 인스턴스 삭제 후 소켓 닫기
	c.setUserState(LOGOFF);
}