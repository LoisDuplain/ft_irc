#pragma once

#include "commands/PassCommand.hpp"

PassCommand::PassCommand(Server &server)	:	ACommand(server, "PASS", false, false, false)
{
}
PassCommand::~PassCommand(void)
{
}

bool	PassCommand::execute(User *commandSender, std::vector<std::string> args)
{
	commandSender->sendMessage(NULL, "Super mot de passe");
	return true;
}