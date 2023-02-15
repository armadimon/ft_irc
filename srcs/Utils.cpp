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

// int main()
// {
// 	std::string s = "abcdaaaaa";
// 	std::vector<std::string> str = string_split(s, " ");

// 	std::vector<std::string>::iterator it = str.begin();
// 	for (; it < str.end(); it++)
// 		std::cout << *it;
// 	return 0;
// }