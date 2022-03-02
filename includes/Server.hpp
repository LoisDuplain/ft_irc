#pragma once

#include <iostream>
#include <string>

class Server
{
private:
	const std::string _port;
	const std::string _password;
public:
	Server(std::string port, std::string passord);
	~Server();

	const std::string getPort(void)	const;
	const std::string getPassword(void)	const;
};
