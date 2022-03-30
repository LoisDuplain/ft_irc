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
	{
		commandSender->sendMessage(NULL, "Please specify a nickname");
		return false;
	}
	
	if (commandSender->getNickname() != "" && getServer()->getUser(args.at(1)) != NULL)
	{
		commandSender->sendMessage(NULL, "Nickname already in use");
		return false;
	}

	if (checkBadCharacters(args.at(1)))
	{
		commandSender->sendMessage(NULL, "Bad characters");
		return false;
	}

	commandSender->setNickname(args.at(1));
	commandSender->sendMessage(NULL, "Your nickname has been set to: " + args.at(1));

	if (!commandSender->getNickname().empty() && !commandSender->getUsername().empty())
	{
		commandSender->setAuthenticated(true);
		commandSender->sendMessage(NULL, "Your are now authenticated.");
		if (commandSender->getNickname() == "op")
		{
			commandSender->setOp(true);
			commandSender->sendMessage(NULL, "Your are now an operator.");
		}
	}
	return true;
}