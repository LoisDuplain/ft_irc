#pragma once

#include "ACommand.hpp"

class JoinCommand	:	public ACommand
{
public:
	JoinCommand(Server *server);
	~JoinCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
