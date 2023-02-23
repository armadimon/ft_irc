#include "../includes/Utils.hpp"
#include "../includes/Server.hpp"

void	reply(int fd, int replyNum, std::string msg)
{
	std::stringstream ss;

	ss << ":ircserv " << replyNum << " " << msg << " ";

	std::cout << "[" << ss.str() << "]" << std::endl;
	switch (replyNum)
	{
	case 353:
		break;
	case 366:
		ss << ":End of NAMES list\r\n";
	default:
		break;
	}
	send(fd, ss.str().c_str(),ss.str().size(), 0);
}