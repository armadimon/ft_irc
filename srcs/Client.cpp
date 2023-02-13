#include "../includes/Client.hpp"



std::vector<std::string> string_split(std::string str, const char* delimiter);

Client::Client(int fd)
	:fd(fd)
{
	// cmdlist["PASS"] = PASS;
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


	std::vector<std::string>::iterator iter = this->msg.begin();
	for (; iter < this->msg.end(); iter++)
	{

		std::cout << "msg : [" << *iter << "]   size : " << msg.size() << std::endl;
	}
	return (0); 
}

void	Client::excute()
{
	// prefix | command | param - ( middle trailing)
	// map<std::string, void(*)(Client &)> = cmdlist;
	std::vector<std::string>::iterator it = this->msg.begin();
	while (it != this->msg.end())
	{
		// cmdlist[cmd];
		it++;
	}
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