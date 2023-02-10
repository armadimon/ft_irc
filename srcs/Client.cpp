#include "../includes/Client.hpp"

Client::Client(int fd)
	:fd(fd)
{
}

void Client::clientRead()
{
	  int	r;

  	r = recv(fd, bufRead, 1024, 0);
	  std::cout << bufRead << std::endl;
  	if (r <= 0)
    {
      close(fd);
      printf("client #%d gone away\n", fd);
    }
}

Client::Client()
{ }

Client::~Client()
{

}