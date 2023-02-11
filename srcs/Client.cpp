#include "../includes/Client.hpp"

Client::Client(int fd)
	:fd(fd)
{
}

Client::Client()
{ }

Client::~Client()
{

}


char	*Client::getBuf()
{
	return (this->bufRead);
}

int		Client::getFD()
{
	return (this->fd);			
}