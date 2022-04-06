#include "commands/PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server)	:	ACommand(server, "PRIVMSG", true, true, false)
{
}
PrivMsgCommand::~PrivMsgCommand(void)
{
}

bool	PrivMsgCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 2 || args.at(2)[0] != ':' || args.at(2)[1] == '\0')
	{
		commandSender->sendMessage(NULL, "Wrong arguments");
		return false;
	}

	std::vector<std::string> recs = parseArg(args.at(1));
	User *usr;
	Channel *ch;

	std::string message = args.at(2);
	for (size_t i = 3; i < args.size(); i++)
		message.append(" ").append(args.at(i));
	message.erase(message.begin());
	for (size_t i = 0; i < recs.size(); i++)
	{
		usr = getServer()->getUser(recs.at(i));
		ch = getServer()->getChannel(recs.at(i));
		if (usr != NULL)
			usr->sendMessage(commandSender, message);
		else if (ch != NULL)
		{
			if (ch->getUser(commandSender->getNickname()) == commandSender)
				ch->sendMessage(commandSender, message);
			else
				commandSender->sendMessage(NULL, "You are not in this channel");
		}
		else
			commandSender->sendMessage(NULL, "Wrong arguments");
	}
	return true;
}