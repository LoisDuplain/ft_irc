#pragma once

#include "ACommand.hpp"

class UserCommand	:	public ACommand
{
public:
	UserCommand(Server *server);
	~UserCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
