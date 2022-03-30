#include "commands/PassCommand.hpp"

PassCommand::PassCommand(Server *server)	:	ACommand(server, "PASS", false, false, false)
{
}
PassCommand::~PassCommand(void)
{
}

bool	PassCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 1)
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}
	if (commandSender->isConnected())
	{
		commandSender->sendMessage(NULL, "You are already connected");
		return false;
	}

	if (args.at(1) != getServer()->getPassword())
		return false;

	commandSender->setConnected(true);
	commandSender->sendMessage(NULL, "You are now connected. You can now identify yourself using the NICK and USER commands.");
	
	return true;
}