#include "commands/NickCommand.hpp"

NickCommand::NickCommand(Server *server)	:	ACommand(server, "NICK", true, false, false)
{
}
NickCommand::~NickCommand(void)
{
}

bool	NickCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 1 || args.at(1).empty())
		return false;
	commandSender->setNickname(args.at(1));
	commandSender->sendMessage(NULL, "Your nickname have been set to: " + args.at(1));
	return true;
}