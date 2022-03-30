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
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NONICKNAMEGIVEN, "", ""));
		return false;
	}
	
	if (commandSender->getNickname() != "" && getServer()->getUser(args.at(1)) != NULL)
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NICKNAMEINUSE, args.at(1), ""));
		return false;
	}

	if (checkBadCharacters(args.at(1)))
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_ERRONEUSNICKNAME, args.at(1), ""));
		return false;
	}

	if (getServer()->getUser(args.at(1)) != NULL)
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NICKCOLLISION, args.at(1), ""));
		return false;
	}

	commandSender->setNickname(args.at(1));
	commandSender->sendMessage(NULL, "Your nickname have been set to: " + args.at(1));

	if (commandSender->getUsername() != "" && commandSender->getNickname() != "")
	{
		commandSender->setAuthenticated(true);
		commandSender->sendMessage(NULL, "Your are now authenticated.");
	}
	return true;
}