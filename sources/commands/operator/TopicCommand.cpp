#include "commands/operator/TopicCommand.hpp"

TopicCommand::TopicCommand(Server *server)	:	ACommand(server, "TOPIC", true, true, true)
{
}
TopicCommand::~TopicCommand(void)
{
}

bool	TopicCommand::execute(User *commandSender, std::vector<std::string> args)
{

	if (args.size() <= 1 || args.at(1).empty())
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
		return false;
	}

	std::string channel_name = stringToLowerCase(args.at(1));
	Channel *ch = getServer()->getChannel(channel_name);

	if (ch == NULL)
	{
		commandSender->sendSTDPacket(ERR_NOTONCHANNEL, "TOPIC " + channel_name + " :" + "Channel not found");
		return false;
	}

	if (ch->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendSTDPacket(ERR_CHANOPRIVSNEEDED, "TOPIC " + channel_name + " :" + "You're not channel operator");
		return false;
	}

	ch->setTopic(args.at(2));
	return true;
}