#include "commands/PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(Server *server)	:	ACommand(server, "PRIVMSG", true, true, false)
{
}
PrivMsgCommand::~PrivMsgCommand(void)
{
}

bool	PrivMsgCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 2)
	{
		commandSender->sendSTDPacket(ERR_NOTEXTTOSEND, "PRIVMSG :Please specify a text to send");
		return false;
	}

	std::string message = args.at(2);
	if (message.at(0) == ':')
		message.erase(message.begin());
	for (size_t i = 3; i < args.size(); i++)
		message.append(" ").append(args.at(i));

	if (message.empty())
	{
		commandSender->sendSTDPacket(ERR_NOTEXTTOSEND, "PRIVMSG :Please specify a text to send");
		return false;
	}

	std::vector<std::string> targets = parseArg(args.at(1));

	for (size_t i = 0; i < targets.size(); i++)
	{
		User *targetUser = getServer()->getUser(targets.at(i));

		if (targets.at(i).at(0) == '#')
		{
			Channel *targetChannel = getServer()->getChannel(targets.at(i));

			if (targetChannel != NULL && targetChannel->getUser(commandSender->getNickname()) == commandSender)
				targetChannel->sendMessage(commandSender, message);
			else
				commandSender->sendSTDPacket(ERR_CANNOTSENDTOCHAN, "PRIVMSG " + targets.at(i) + " :Cannot send to the channel");
		}
		else if (targetUser != NULL)
			targetUser->sendMessage(commandSender, message);
		else
			commandSender->sendSTDPacket(ERR_CANNOTSENDTOCHAN, "PRIVMSG " + targets.at(i) + " :Cannot find nickname");
	}
	return true;
}