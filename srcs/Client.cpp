#include "../includes/Client.hpp"

Client::Client(int fd)
	:fd(fd), userState(DEFAULT)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
	cmdList["PASS"] = cmdPass;
	cmdList["USER"] = cmdUser;
	cmdList["NICK"] = cmdNick;
	cmdList["PRIVMSG"] = cmdPrivMsg;
	cmdList["NOTICE"] = cmdNotice;
	cmdList["JOIN"] = cmdJoin;
	cmdList["KICK"] = cmdKick;
	cmdList["PART"] = cmdPart;
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
			std::cout << "check 1 " << std::endl;
			this->excute(cmd);
		}

	}
	msgClear();
	return (0); 
}

void	Client::msgClear()
{
	msg.clear();
	msg.reserve(0);
}

void	Client::excute(Command cmd)
{
	if (cmdList.find(cmd.getCmd()) != cmdList.end())
		cmdList[cmd.getCmd()](cmd, this->getFD());
	if (this->userState == READY)
		registerClient();
	std::cout << "state : " << userState << std::endl;

}

void	Client::registerClient() // 매개변수에 server class를 넣을 것인가 아니()
{
	if (this->nickName.size() > 0 &&
		this->hostName.size() > 0 &&
		this->userName.size() > 0 &&
		this->realName.size() > 0 )
		userState = REGISTER;
}


int	Client::addmyChannelList(std::string channel_name)
{
	std::vector<std::string>::iterator strIter = myChannelList.begin();

	for (; strIter != myChannelList.end(); strIter++)
	{
		if (*strIter == channel_name)
			return (0);
	}
	this->myChannelList.push_back(channel_name);
	return (1);
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

void Client::setUserState(State state)
{
	userState = state;
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

int		Client::findChannelFromList(std::string chName)
{
	std::vector<std::string>::iterator vecIter = myChannelList.begin();

	for (; vecIter != myChannelList.end(); vecIter++)
	{
		if (*vecIter == chName)
			return (1);
	}
	return (0);
}