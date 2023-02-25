#include "../includes/Client.hpp"

void	cmdPass(Command cmd, int fd);
void	cmdUser(Command cmd, int fd);
void	cmdNick(Command cmd, int fd);
void	cmdPrivMsg(Command cmd, int fd);
void	cmdJoin(Command cmd, int fd);

Client::Client(int fd)
	:fd(fd), userState(DEFAULT)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
	cmdList["PASS"] = cmdPass;
	cmdList["USER"] = cmdUser;
	cmdList["NICK"] = cmdNick;
	cmdList["PRIVMSG"] = cmdPrivMsg;
	cmdList["JOIN"] = cmdJoin;
	// cmdList["KICK"] = cmdKick;
}

Client::Client()
{ }

Client::~Client()
{

}

int	Client::parseMSG(Server *server, std::string tempStr)
{
	std::vector<Command> cmdList;
	std::vector<std::string> strVec;
	strVec = string_split(tempStr, "\r\n");
	std::vector<std::string>::iterator strIter = strVec.begin();
	for (; strIter < strVec.end(); strIter++)
	{
		std::cout << "check cmd" << std::endl;
		Command cmd(*strIter, server);
		std::cout << cmd.getCmd() << std::endl;
		cmdList.push_back(cmd);
	}
	std::vector<Command>::iterator cmdIter = cmdList.begin();
	for (; cmdIter < cmdList.end(); cmdIter++)
	{
		this->excute(*cmdIter);
	}
	return (0); 
}

void	Client::excute(Command cmd)
{
	// std::cout << "msg : " << *(msg.begin()) << std::endl;
	if (cmdList.find(cmd.getCmd()) != cmdList.end())
		cmdList[cmd.getCmd()](cmd, this->getFD());
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

void	Client::removeChannelFromList(std::string channel_name)
{
	std::vector<std::string>::iterator it = this->myChannelList.begin();
	for (; it < this->myChannelList.end(); it++)
	{
		if (channel_name == *it)
			this->myChannelList.erase(it);
	}
}