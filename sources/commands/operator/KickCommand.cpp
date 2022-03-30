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

	if (args.size() <= 2 || args.at(1).empty())
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}

	channels = parseArg(args.at(1));
	users = parseArg(args.at(2));

	if (channels.size() != users.size())
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}

	std::string reason;
	if (args.size() > 3)
	{
		reason = args.at(3);
		for (size_t i = 4; i < args.size(); i++)
		reason.append(" ").append(args.at(i));
	}

	while (i < channels.size())
	{
		Channel *ch = getServer()->getChannel(channels.at(i));
		if (ch == NULL)
			commandSender->sendMessage(NULL, "Channel not found");
		else
		{
			User *us = ch->getUser(users.at(i));
			if (us == NULL)
				commandSender->sendMessage(NULL,  "User not found");
			else
			{
				ch->removeUser(us);
				us->getChannels().erase(ch->getName());

				std::string tmp = "You have been kicked from the channel :";
				tmp.append(ch->getName());
				if (args.size() > 3)
					tmp.append(" for reason :").append(reason);
				else
					tmp.append(".");
				us->sendMessage(NULL, tmp);
				tmp.clear();

				tmp = "You have kicked user :";
				tmp.append(us->getNickname()).append(".");
				commandSender->sendMessage(NULL, tmp);
				tmp.clear();

				tmp = us->getNickname();
				tmp.append(" was kicked for the channel :").append(ch->getName());
				if (args.size() > 3)
					tmp.append(" for reason :").append(reason);
				else
					tmp.append(".");
				ch->sendMessage(NULL, tmp);
			}
		}
		i++;
	}

	return true;
}