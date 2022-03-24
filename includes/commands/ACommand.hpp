#pragma once

#include <string>
#include <vector>

class Server;
class User;

class ACommand
{
private:
			Server	&_server;
protected:
			std::string	_command;

			bool	_needConnected;
			bool	_needAuthenticated;
			bool	_needOp;

			/* Constructors */
public:
			ACommand(Server &server, std::string command, bool needConnected, bool needAuthenticated, bool needOp);
			virtual	~ACommand(void);

			/* Command execution */
private:
			bool	preExecute(User *commandSender, std::vector<std::string> args);
public:
			virtual	bool	execute(User *commandSender, std::vector<std::string> args);

			/* Getters */
					Server		&getServer()		const;
			const	std::string	getCommand()		const;
					bool		needConnected()		const;
					bool		needAuthenticated()	const;
					bool		needOp()			const;
};

#include "Server.hpp"
#include "User.hpp"