#include "../includes/Server.hpp"

Server::Server()
{
	this->is_set = 0;
	this->fd_num = 0;

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
		throw std::runtime_error("error: accept");
	clients[new_socket] = Client(new_socket);
}

void Server::createSocket()
{
	int					socket_fd;
	struct sockaddr_in	socket_in;
	struct protoent		*pe;

	pe = getprotobyname("tcp");
	if (pe == NULL)
		throw std::runtime_error("error: getprotobyname");
	socket_in.sin_family = AF_INET;
	socket_in.sin_addr.s_addr = INADDR_ANY;
	socket_in.sin_port = htons(this->port);
	socket_fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (socket_fd == -1)
		throw std::runtime_error("error: socket");
	fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	if (bind(socket_fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) == -1)
		throw std::runtime_error("Error: bind");
	if (listen(socket_fd, 42) == -1)
		throw std::runtime_error("error: listen");
	
	FD_SET(socket_fd, &read_fds);
}

void Server::doSelect() {
	is_set = select(MAX_FD, &read_fds, &write_fds, NULL, NULL);
}

void Server::start()
{
	createSocket();
	while (true)
	{
		doSelect();
		acceptClient();
		int i = 0;
		while (i < MAX_FD && is_set > 0)
		{
			if (FD_ISSET(i, &read_fds))
				clients[i].clientRead();
			i++;
		}
	}
}

void Server::setPass(char *pw)
{
	this->password = atoi(pw);
}

void Server::setPort(char *port)
{
	this->port = atoi(port);
}