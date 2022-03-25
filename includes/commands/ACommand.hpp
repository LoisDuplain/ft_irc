#pragma once

#include <string>
#include <vector>

class Server;
class User;

class ACommand
{
private:
			Server	*_server;
protected:
			std::string	_label;

			bool	_needConnected;
			bool	_needAuthenticated;
			bool	_needOp;

			/* Constructors */
public:
			ACommand(Server *server, std::string label, bool needConnected, bool needAuthenticated, bool needOp);
			virtual	~ACommand(void);

			/* Command execution */
public:
			bool	preExecute(User *commandSender, std::vector<std::string> args);
			virtual	bool	execute(User *commandSender, std::vector<std::string> args);

			/* Getters */
					Server		*getServer()		const;
			const	std::string	getLabel()			const;
					bool		needConnected()		const;
					bool		needAuthenticated()	const;
					bool		needOp()			const;
};

#include "Server.hpp"
#include "User.hpp"