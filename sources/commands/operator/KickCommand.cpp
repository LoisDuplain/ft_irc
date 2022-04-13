#include "commands/operator/KickCommand.hpp"

KickCommand::KickCommand(Server *server)	:	ACommand(server, "KICK", true, true, true)
{
}
KickCommand::~KickCommand(void)
{
}

bool	KickCommand::execute(User *commandSender, std::vector<std::string> args)
{

	std::vector<std::string> channels;
	std::vector<std::string> users;
	size_t i = 0;

	if (args.size() <= 3 || args.at(1).empty())
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
		return false;
	}

	channels = parseArg(args.at(1));
	users = parseArg(args.at(2));

	if (channels.size() != users.size())
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");
		return false;
	}

	std::string reason;
	if (args.size() > 3)
	{
		reason = args.at(3);
		for (size_t i = 4; i < args.size(); i++)
		reason.append(" ").append(args.at(i));
	}
	std::string channel_name;
	while (i < channels.size())
	{
		channel_name = stringToLowerCase(args.at(1));
		Channel *channel = getServer()->getChannel(channel_name);
		if (channel == NULL)
			commandSender->sendSTDPacket(ERR_NOSUCHCHANNEL, "KICK " + channel_name + " :Channel not found");
		else
		{
			User *us = channel->getUser(users.at(i));
			if (channel->getOperatorUser(commandSender->getNickname()) != commandSender)
				commandSender->sendSTDPacket(ERR_CHANOPRIVSNEEDED, "KICK " + channel_name + " :" + "You're not channel operator");
			else if (us == NULL)
				commandSender->sendSTDPacket(ERR_NOSUCHNICK, "KICK " + users.at(i) + " :No such nick/channel");
			else
			{
				channel->removeUser(us);
				us->getChannels().erase(channel->getName());
				channel->sendRefreshedUserList();
			}
		}
		i++;
	}

	return true;
}