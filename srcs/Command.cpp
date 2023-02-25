#include "../includes/Command.hpp"

Command::Command() {}

Command::Command(std::string msg, Server *server)
: server(server)
{
	std::cout << "cmd cons" << std::endl;
	std::cout << msg << std::endl;
	std::vector<std::string> strList;
	if (msg.empty())
		return ;
	if (msg.find_first_of(":") != std::string::npos)
	{
		std::cout << "check 1" << std::endl;
		std::vector<std::string> trailing = string_split(msg, ":"); 
		strList = string_split(trailing[0], " "); 
		std::string tempStr = ":";
		tempStr += trailing[1];
		trim(tempStr, "\r\n");
		this->trailing = tempStr;
	}
	else
		strList = string_split(msg, " ");
	std::vector<std::string>::iterator strIter = strList.begin();
	for (; strIter < strList.end(); strIter++)
	{
		std::cout << "strIter : " << *strIter << std::endl;
		if (strIter == strList.begin())
			this->cmd = *strIter;
		else
			this->params.push_back(*strIter);
	}
}

Command::~Command() {}

std::string Command::getCmd()
{
	return (this->cmd);
}

Server &Command::getServer()
{
	return (*server);
}

std::vector<std::string> &Command::getParams()
{
	return (this->params);
}

std::string Command::getTrailing()
{
	return (this->trailing);
}
