#pragma once

#include "../ACommand.hpp"

class KickCommand	:	public ACommand
{
public:
	KickCommand(Server *server);
	~KickCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
