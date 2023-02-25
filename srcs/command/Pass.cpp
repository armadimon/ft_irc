#include "../../includes/Command.hpp"

void	cmdPass(Command cmd, int fd)
{
	// if (str.size() < 1) // ERR_NEEDMOREPARAMS 461
	Client &c = cmd.getServer().getClient(fd);

	std::vector<std::string>::iterator it = cmd.getParams().begin();
	if (c.getUserState() == DEFAULT)
	{
		for (; it < cmd.getParams().end(); it++)
		{		
				std::cout << "server_pass : [" << cmd.getServer().getPass() << std::endl;
				std::cout << "input_pass : [" << *it << std::endl;

				
				if (cmd.getServer().getPass() == *it)
					c.setUserState();
				std::cout << "State : " << c.getUserState() << std::endl;
		}
	}
	if (c.getUserState() == REGISTER)
		; // ERR_ALREADYREGISTRED 462 
}