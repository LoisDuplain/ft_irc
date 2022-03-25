#include "commands/PassCommand.hpp"

PassCommand::PassCommand(Server *server)	:	ACommand(server, "PASS", false, false, false)
{
}
PassCommand::~PassCommand(void)
{
}

bool	PassCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 1 || args.at(1) != getServer()->getPassword())
		return false;
	commandSender->setConnected(true);
	return true;
}