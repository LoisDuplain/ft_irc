#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>

class Server
{
private:
	const int _port;
	const std::string _password;
public:
	Server(std::string port, std::string passord);
	~Server();

	int getPort(void)	const;
	const std::string getPassword(void)	const;
};
