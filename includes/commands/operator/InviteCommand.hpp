#pragma once

#include "../ACommand.hpp"

class InviteCommand	:	public ACommand
{
public:
	InviteCommand(Server *server);
	~InviteCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
