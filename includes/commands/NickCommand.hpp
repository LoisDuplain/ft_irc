#pragma once

#include "ACommand.hpp"

class NickCommand	:	public ACommand
{
public:
	NickCommand(Server *server);
	~NickCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
