#include "../includes/Utils.hpp"
#include "../includes/Server.hpp"

void	reply(int fd, int replyNum, std::string msg)
{
	std::stringstream ss;
	std::vector<std::string> params = string_split(msg, ",");

	if (params.size() > 1)
		std::cout << "reply parameter : " << params[0] << std::endl;
	else
		std::cout << "reply parameter : " << msg << std::endl;
	
	switch (replyNum)
	{
	case 353:
		break;
	case 366:
		ss << " :End of NAMES list\r\n";
		break;
	case 403:
		ss << " :No such channel\r\n";
		break;
	case 411:
		ss << " :No recipient given (PRIVMSG)\r\n";
		break;
	case 412:
		ss << " :No text to send\r\n";
		break;
	case 431:
		ss << " :No nickname given\r\n";
		break;
	case 432:
		ss << " :Erroneus nickname\r\n";
		break;
	case 433:
		ss << " :Nickname is already in use\r\n";
		break;
	case 441:
		ss << " " << params[0] << " " << params[1];
		ss << " :They aren't on that channel\r\n";
		break;
	case 436:
		ss << ":Nickname collision KIL\r\n";
		break;
	case 442:
		ss << " :You're not on that channel\r\n";
		break;
	case 461:
		ss << " :Not enough parameters\r\n";
		break;
	case 462:
		ss << " :You may not reregister\r\n";
		break;
	case 475:
		ss << " :Cannot join channel (+k)\r\n";
		break;
	case 476:
		// ERR_BADCHANMASK
		break;
	case 482:
		ss << " :You're not channel operator\r\n";
		break;
	default:
		break;
	}
	std::cout << "reply : [" << ss.str() << "]" << std::endl;
	send(fd, ss.str().c_str(),ss.str().size(), 0);
}