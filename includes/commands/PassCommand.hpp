#pragma once

#include "ACommand.hpp"

class PassCommand	:	public ACommand
{
public:
	PassCommand(Server &server);
	~PassCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
