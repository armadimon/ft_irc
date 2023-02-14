#include "../../includes/Client.hpp"

void	cmdPass(Client *c, std::vector<std::string> str)
{
	std::vector<std::string>::iterator it = str.begin();
	int cnt = 0;

	for (; it < str.end(); it++)
	{
		if (cnt == 0)
			std::cout << "PASS CMD check : " << c->getFD() << std::endl;
	}
}