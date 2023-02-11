#include "../includes/Server.hpp"

Server::Server()
{
	this->is_set = 0;
	this->fd = 0;

	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
}

Server::~Server() {}

void Server::acceptClient()
{
	int					new_socket;
	struct sockaddr_in	new_socket_in;
	socklen_t			new_socket_len;

	new_socket_len = sizeof(new_socket_in);
	new_socket = accept(this->fd, (struct sockaddr *)&new_socket_in, &new_socket_len);
	if (new_socket == -1)
		throw std::runtime_error("Error: accept");
	clients[new_socket] = new Client(new_socket);
	std::cout << "Client #" << new_socket << " is Connected!" << std::endl;
	if (new_socket > fd_max)
		fd_max = new_socket;
	FD_SET(new_socket, &read_fds);
}

void Server::createSocket()
{
	struct sockaddr_in	socket_in;
	struct protoent		*pe;

	pe = getprotobyname("tcp");
	if (pe == NULL)
		throw std::runtime_error("Error: getprotobyname");
	socket_in.sin_family = AF_INET;
	socket_in.sin_addr.s_addr = INADDR_ANY;
	socket_in.sin_port = htons(this->port);
	fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		throw std::runtime_error("Error: socket");
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (bind(fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) == -1)
		throw std::runtime_error("Error: bind");
	if (listen(fd, 42) == -1)
		throw std::runtime_error("Error: listen");
	FD_SET(fd, &read_fds);
	fd_max = fd;
}

void Server::doSelect() {
	is_set = select(fd_max + 1, &cpy_read_fds, &write_fds, NULL, NULL);
	if (is_set == -1)
		throw std::runtime_error("Error: select");
}

void Server::clientRead(int client_fd)
{
	int	r;
	char* bufRead = this->getClient(client_fd)->getBuf();

  	r = recv(client_fd, bufRead, 1024, 0);
	std::cout << bufRead << std::endl;
  	if (r <= 0)
    {
		FD_CLR(client_fd, &read_fds);
    	close(client_fd);
    	printf("client #%d gone away\n", client_fd);
    }
}

void Server::start()
{
	createSocket();
	while (true)
	{
		cpy_read_fds = read_fds;
		doSelect();
		int i = 0;
		while (i < MAX_FD && is_set > 0)
		{
			if (FD_ISSET(i, &cpy_read_fds))
			{
				if (i == this->fd)
				{
					acceptClient();
					is_set--;
				}
				else
				{
					clientRead(clients[i]->getFD());
					is_set--;
				}
			}
			i++;
		}
	}
}


/*
METHOD :: GETTER
*/

Client *Server::getClient(int client_fd)
{
	return (this->clients[client_fd]);
}


/*
METHOD :: SETTER
*/

void Server::setPass(char *pw)
{
	this->password = atoi(pw);
}

void Server::setPort(char *port)
{
	this->port = atoi(port);
}