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

Client::Client() {}

Client::~Client() {}

int	Client::parseMSG(Server *server, std::string tempStr)
{
	std::vector<Command>		cmdList;
	std::vector<std::string>	strVec;
	size_t						cmdCnt = 0;
	size_t						pos = 0;

	while (pos != std::string::npos)
	{
		pos = tempStr.find("\n", pos);
		if (pos != std::string::npos)
		{
			pos++;
			cmdCnt++;
		}
	}
	if (msg.length() > 0)
		tempStr = msg + tempStr;
	strVec = string_split(tempStr, "\r\n");
	std::vector<std::string>::iterator strIter = strVec.begin();
	for (; strIter < strVec.end(); strIter++)
	{
		if (strIter + 1 == strVec.end() && strVec.size() != cmdCnt)
		{
			msg = *strIter;
			return (0);
		}
		else
		{
			Command cmd(*strIter, server);
			this->excute(cmd);
		}

	}
	msgClear();
	// std::vector<Command>::iterator cmdIter = cmdList.begin();
	// for (; cmdIter < cmdList.end(); cmdIter++)
	// {
	// 	this->excute(*cmdIter);
	// }
	return (0); 
}

void	Client::msgClear()
{
	msg.clear();
	msg.reserve(0);
}

void	Client::excute(Command cmd)
{
	// std::cout << "msg : " << *(msg.begin()) << std::endl;
	if (cmdList.find(cmd.getCmd()) != cmdList.end())
		cmdList[cmd.getCmd()](cmd, this->getFD());
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