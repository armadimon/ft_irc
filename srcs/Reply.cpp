#include "../includes/Utils.hpp"
#include "../includes/Server.hpp"

void	reply(int fd, int replyNum, std::string msg)
{
	std::stringstream ss;

	ss << ":ircserv " << replyNum << " " << msg << " ";

	switch (replyNum)
	{
	case 353:
		break;
	case 366:
		ss << ":End of NAMES list\r\n";
		break;
	case 475:
		ss << ":Cannot join channel (+k)\r\n";
		break;
	default:
		break;
	}
	std::cout << "reply : [" << ss.str() << "]" << std::endl;
	send(fd, ss.str().c_str(),ss.str().size(), 0);
}