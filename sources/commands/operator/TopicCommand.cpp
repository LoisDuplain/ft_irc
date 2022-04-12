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

	Channel *ch = getServer()->getChannel(args.at(1));

	if (ch == NULL)
	{
		commandSender->sendSTDPacket(ERR_NOTONCHANNEL, "TOPIC " + args.at(1) + " :" + "Not enough parameters");
		return false;
	}

	if (ch->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendSTDPacket(ERR_CHANOPRIVSNEEDED, "TOPIC " + args.at(1) + " :" + "You're not channel operator");
		return false;
	}

	if (args.size() == 2)
		ch->sendMessage(NULL, ch->getTopic());
	else
	{
		ch->setTopic(args.at(2));
		std::string tmp = commandSender->getNickname();
		tmp.append(" change channel topic to :");
		tmp.append(ch->getTopic());
		tmp.append("\n");
		ch->sendMessage(NULL, tmp);
	}
	return true;
}