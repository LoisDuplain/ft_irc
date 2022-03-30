#pragma once

#include "../ACommand.hpp"

class ModeCommand	:	public ACommand
{
public:
	ModeCommand(Server *server);
	~ModeCommand(void);

	bool	modeOp(Channel *ch, User *commandSender, std::vector<std::string> args);
	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
