#include "commands/UserCommand.hpp"

UserCommand::UserCommand(Server *server)	:	ACommand(server, "USER", true, false, false)
{
}
UserCommand::~UserCommand(void)
{
}

bool	UserCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 4 || args.at(1).empty() || args.at(4)[0] != ':' || args.at(4)[1] == '\0')
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}

	if (!commandSender->getUsername().empty())
	{
		commandSender->sendMessage(NULL, "You are already registered");
		return false;
	}
	
	commandSender->setUsername(args.at(1));
	commandSender->sendMessage(NULL, "Your username has been set to: " + args.at(1));

	std::string real_name = args.at(4);
	for (size_t i = 5; i < args.size(); i++)
		real_name.append(" ").append(args.at(i));
	real_name.erase(real_name.begin());
	commandSender->setRealName(real_name);
	commandSender->sendMessage(NULL, "Your realname has been set to: " + real_name);

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