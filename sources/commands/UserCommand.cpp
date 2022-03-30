#include "commands/UserCommand.hpp"

UserCommand::UserCommand(Server *server)	:	ACommand(server, "USER", true, false, false)
{
}
UserCommand::~UserCommand(void)
{
}

bool	UserCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 4 || args.at(1).empty() || args.at(4)[0] != ':' || !args.at(4)[1])
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NEEDMOREPARAMS, "USER", ""));
		return false;
	}

	if (commandSender->getUsername() != "")
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_ALREADYREGISTRED, "", ""));
		return false;
	}

	commandSender->setUsername(args.at(1));
	std::string tmp = args.at(4);
	size_t i = 5;
	while (i < args.size())
	{
		tmp.append(" ");
		tmp.append(args.at(i++));
	}

	tmp.erase(tmp.begin());
	
	commandSender->setRealName(tmp);
	commandSender->sendMessage(NULL, "Your username have been set to: " + args.at(1));
	commandSender->sendMessage(NULL, "Your realname have been set to: " + tmp);

	if (commandSender->getUsername() != "" && commandSender->getNickname() != "")
	{
		commandSender->setAuthenticated(true);
		commandSender->sendMessage(NULL, "Your are now authenticated.");
	}

	return true;
}