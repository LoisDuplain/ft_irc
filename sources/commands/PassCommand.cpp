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
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
		return false;
	}
	if (commandSender->isConnected())
	{
		commandSender->sendSTDPacket(ERR_ALREADYREGISTRED, "PASS :You may not reregister");
		return false;
	}

	if (args.at(1) != getServer()->getPassword())
		return false;

	commandSender->setConnected(true);
	
	return true;
}