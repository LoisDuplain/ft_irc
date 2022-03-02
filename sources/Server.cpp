#include "Server.hpp"

Server::Server(std::string port, std::string password)	:	_port(atoi(port.c_str())), _password(password)
{
}

Server::~Server()
{
}

int Server::getPort(void)	const
{
	return this->_port;
}

const std::string Server::getPassword(void)	const
{
	return this->_password;
}