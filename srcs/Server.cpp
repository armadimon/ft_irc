#include "includes/Server.hpp"

Server::Server()
{
}

void Server::acceptClient()
{
	int					new_socket;
	struct sockaddr_in	new_socket_in;
	socklen_t			new_socket_len;

	new_socket_len = sizeof(new_socket_in);
	new_socket = accept(this->fd, (struct sockaddr *)&new_socket_in, &new_socket_len);
	clients[new_socket] = Client(new_socket);
}

void Server::createSocket(int port)
{
	int					socket_fd;
	struct sockaddr_in	socket_in;
	struct protoent		*pe;

	pe = getprotobyname("tcp");
	if (pe == NULL)
		throw ServerException(std::string("error: getprotobyname"));
	socket_in.sin_family = AF_INET;
	socket_in.sin_addr.s_addr = INADDR_ANY;
	socket_in.sin_port = htons(this->port);
	socket_fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (socket_fd == -1)
		throw ServerException(std::string("error: socket"));
	if (bind(socket_fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) == -1)
		throw ServerException(std::string("Error: bind"));
	if (listen(socket_fd, 42) == -1)
		throw ServerException(std::string("error: listen"));
}

void Server::setPass(char *pw)
{
	this->password = atoi(pw);
}

void Server::setPort(char *port)
{
	this->port = atoi(port);
}