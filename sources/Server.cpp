#include "Server.hpp"

Server::Server(std::string port, std::string password)	:	_port(port), _password(password)
{
}

Server::~Server()
{
}

const std::string Server::getPort(void)	const
{
	return this->_port;
}

const std::string Server::getPassword(void)	const
{
	return this->_password;
}