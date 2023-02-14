#include "../includes/Client.hpp"

std::vector<std::string> string_split(std::string str, const char* delimiter);

void	cmdPass(Server *s, int fd, std::vector<std::string> str);
void	cmdUser(Server *s, int fd, std::vector<std::string> str);
void	cmdNick(Server *s, int fd, std::vector<std::string> str);
void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str);

Client::Client(int fd)
	:fd(fd), userState(DEFAULT)
{
	// fcntl(fd, F_SETFL, O_NONBLOCK);
	cmdList["PASS"] = cmdPass;
	cmdList["USER"] = cmdUser;
	cmdList["NICK"] = cmdNick;
	cmdList["PRIVMSG"] = cmdPrivMsg;
}

Client::Client()
{ }

Client::~Client()
{

}

int	Client::parseMSG(std::string tempStr)
{
	if (tempStr.empty()) return (1);

	std::vector<std::string>::iterator it = this->msg.begin();
	for (; it < this->msg.end(); it++)
	{
		(*it).clear();
	}
	msg.clear();
	msg.reserve(0);
	// this->msg = string_split(tempStr, " ");
	if (tempStr.find_first_of(":") != std::string::npos)
	{
		std::cout << "check 1" << std::endl;
		std::vector<std::string> trailing = string_split(tempStr, ":"); 
		this->msg = string_split(trailing[0], " "); 
		this->msg.push_back(trailing[1]);
	}
	else
		this->msg = string_split(tempStr, " ");

	// std::vector<std::string>::iterator iter = this->msg.begin();
	// for (; iter < this->msg.end(); iter++)
	// {

	// 	std::cout << "msg : [" << *iter << "]   size : " << msg.size() << std::endl;
	// }
	return (0); 
}

void	Client::excute(Server *server)
{
	// prefix | command | param - ( middle trailing)
	// map<std::string, void(*)(Client &)> = cmdlist;
	// std::vector<std::string>::iterator it = this->msg.begin();
	// while (it != this->msg.end())
	// {
	// 	if (msg)
	// 	it++;
	// }
	cmdList[*(msg.begin())](server, this->getFD(), msg);
	// registerClient();
}

// void	Client::registerClient() // 매개변수에 server class를 넣을 것인가 아니()
// {
// 	if (this->nickName != 0 
// 		&& this->hostName != 0
// 		&& this->userName != 0 
// 		&& this->realName != =)
// 		userState = REGISTER;
// }


char	*Client::getBuf()
{
	return (this->bufRead);
}

int		Client::getFD()
{
	return (this->fd);
}

std::string Client::getUserName()
{
	return (this->userName);
}
std::string Client::getNickName()
{
	return (this->nickName);
}
std::string Client::getHostName()
{
	return (this->hostName);
}
std::string Client::getRealName()
{
	return (this->realName);
}

State		Client::getUserState()
{
	return (this->userState);
}

void Client::setUserName(std::string str)
{
	userName = str;
}

void Client::setNickName(std::string str)
{
	nickName = str;
}

void Client::setHostName(std::string str)
{
	hostName = str;
}

void Client::setRealName(std::string str)
{
	realName = str;
}

void Client::setUserState()
{
	userState = REGISTER;
}