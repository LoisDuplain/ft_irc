#pragma once

#include "../ACommand.hpp"

class TopicCommand	:	public ACommand
{
public:
	TopicCommand(Server *server);
	~TopicCommand(void);

	virtual bool execute(User *commandSender, std::vector<std::string> args);
};
