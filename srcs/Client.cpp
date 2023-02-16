#include "../includes/Client.hpp"
// #include ""

void	cmdPass(Server *s, int fd, std::vector<std::string> str);
void	cmdUser(Server *s, int fd, std::vector<std::string> str);
void	cmdNick(Server *s, int fd, std::vector<std::string> str);
void	cmdPrivMsg(Server *s, int fd, std::vector<std::string> str);
void	cmdJoin(Server *s, int fd, std::vector<std::string> str);

Client::Client(int fd)
	:fd(fd), userState(DEFAULT)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
	cmdList["PASS"] = cmdPass;
	cmdList["USER"] = cmdUser;
	cmdList["NICK"] = cmdNick;
	cmdList["PRIVMSG"] = cmdPrivMsg;
	cmdList["JOIN"] = cmdJoin;
}

Client::Client()
{ }

Client::~Client()
{

}

int	Client::parseMSG(std::string tempStr)
{
	if (tempStr.empty()) return (1);

	// this->msg = string_split(tempStr, " ");
	if (tempStr.find_first_of(":") != std::string::npos)
	{
		std::cout << "check 1" << std::endl;
		std::vector<std::string> trailing = string_split(tempStr, ":"); 
		this->msg = string_split(trailing[0], " "); 
		std::string tempStr = ":";
		tempStr += trailing[1];
		this->msg.push_back(tempStr);
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
	std::cout << "msg : " << *(msg.begin()) << std::endl;
	if (cmdList.find(*(msg.begin())) != cmdList.end())
		cmdList[*(msg.begin())](server, this->getFD(), msg);
	// registerClient();
	std::vector<std::string>::iterator it = this->msg.begin();
	for (; it < this->msg.end(); it++)
	{
		(*it).clear();
		std::cout << "clean msg : " << *it << std::endl;
	}
	msg.clear();
	msg.reserve(0);
}

// void	Client::registerClient() // 매개변수에 server class를 넣을 것인가 아니()
// {
// 	if (this->nickName != 0 
// 		&& this->hostName != 0
// 		&& this->userName != 0 
// 		&& this->realName != =)
// 		userState = REGISTER;
// }


void	Client::addmyChannelList(std::string channel_name)
{
	this->myChannelList.push_back(channel_name);
}

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

std::vector<std::string>	Client::getmyChannelList()
{
	return (this->myChannelList);
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