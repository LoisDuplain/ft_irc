#include "commands/PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server)	:	ACommand(server, "PRIVMSG", true, true, false)
{
}
PrivMsgCommand::~PrivMsgCommand(void)
{
}

bool	PrivMsgCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 2 || args.at(2)[1] == '\0')
	{
		commandSender->sendMessage(NULL, "Wrong arguments");
		return false;
	}

	std::vector<std::string> targets = parseArg(args.at(1));

	std::string message = args.at(2);
	if (message.at(0) == ':')
		message.erase(message.begin());
	for (size_t i = 3; i < args.size(); i++)
		message.append(" ").append(args.at(i));
	
	for (size_t i = 0; i < targets.size(); i++)
	{
		User *targetUser = getServer()->getUser(targets.at(i));
		Channel *targetChannel = getServer()->getChannel(targets.at(i));
		if (targetUser != NULL)
			targetUser->sendMessage(commandSender, message);
		else if (targetChannel != NULL)
		{
			if (targetChannel->getUser(commandSender->getNickname()) == commandSender)
				targetChannel->sendMessage(commandSender, message);
			else
				commandSender->sendMessage(NULL, "You are not in this channel");
		}
		else
			commandSender->sendMessage(NULL, std::string("Cannot find target: ") + targets.at(i));
	}
	return true;
}