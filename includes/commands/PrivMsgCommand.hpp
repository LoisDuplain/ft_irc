#pragma once

#include "ACommand.hpp"

class PrivMsgCommand	:	public ACommand
{
public:
	PrivMsgCommand(Server *server);
	~PrivMsgCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
