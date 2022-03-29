#include "commands/PassCommand.hpp"

PassCommand::PassCommand(Server *server)	:	ACommand(server, "PASS", false, false, false)
{
}
PassCommand::~PassCommand(void)
{
}

bool	PassCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (commandSender->isConnected())
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_ALREADYREGISTRED, "", ""));
		return false;
	}

	if (args.size() <= 1)
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NEEDMOREPARAMS, "PASS", ""));
		return false;
	}

	if (args.at(1) != getServer()->getPassword())
		return false;

	commandSender->setConnected(true);
	commandSender->sendMessage(NULL, "You are now connected.");
	
	return true;
}