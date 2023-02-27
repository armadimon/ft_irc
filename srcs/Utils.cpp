#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "../includes/Utils.hpp"

std::vector<std::string> string_split(std::string str, const char* delimiter)
{
	std::vector<std::string> res;
	char* cstr = const_cast<char*>(str.c_str());
	char* temp;
	temp = strtok(cstr, delimiter);
	// std::cout << "temp [" << temp << "]" << std::endl;
	// std::cout << "temp len : "<< strlen(temp) << std::endl;
	while (temp != NULL)
	{
		// std::cout << "temp" << temp << std::endl;
		res.push_back(temp);
		temp = strtok(NULL, delimiter);
	}

	return res;
}

std::string &ltrim(std::string &s, std::string delimiter)
{
	s.erase(0, s.find_first_not_of(delimiter));
	return s;
}
// trim from right
std::string &rtrim(std::string &s, std::string delimiter)
{
	s.erase(s.find_last_not_of(delimiter) + 1);
	return s;
}
// trim from left & right
const std::string &trim(std::string &s, std::string delimiter)
{
	return ltrim(rtrim(s, delimiter), delimiter);
}

void broadcast(std::map<std::string, Channel *> tempCh, std::string chName, std::string msg)
{
	std::map<int, std::string> tempClient = tempCh[chName]->getClientList();
	std::map<int, std::string>::iterator clientIter = tempClient.begin();

	clientIter = tempClient.begin();
	for (;clientIter != tempClient.end(); clientIter++)
	{
		int	cFd = clientIter->first;
		send(cFd, msg.c_str(), msg.size(), 0);
		// 요청한 클라이언트에게만 reply
	} 
}

std::string	makePrefix(Client &c)
{	
	std::string	prefix = ":";
	prefix += c.getNickName();
	prefix += "!";
	prefix += c.getUserName();
	prefix += "@";
	prefix += c.getHostName();
	prefix += " ";
	return prefix;
}

// int main()
// {
// 	std::string s = " abcdaaaaa  ";
// 	std::string str = trim(s, " ");

// 	std::cout << str << std::endl;
// 	// std::vector<std::string>::iterator it = str.begin();
// 	// for (; it < str.end(); it++)
// 	// 	std::cout << *it;
// 	return 0;
// }