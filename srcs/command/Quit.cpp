#include "../../includes/Command.hpp"

// QUIT [<Quit message>]
void	cmdQuit(Command cmd, int fd)
{
	std::string message;
	if (cmd.getTrailing().size() > 0)
		message = cmd.getTrailing();
	else
		message = cmd.getParams()[0];

	Server &s = cmd.getServer();

	// 서버에 메시지 보내기
	// 채널에 메시지 보내기
	// 해당 클라이언트 인스턴스 삭제 후 소켓 닫기
	s.removeClient(fd);

}