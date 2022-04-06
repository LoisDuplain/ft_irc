#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand(Server *server)	:	ACommand(server, "JOIN", true, true, false)
{
}
JoinCommand::~JoinCommand(void)
{
}

bool	JoinCommand::execute(User *commandSender, std::vector<std::string> args)
{
	std::vector<std::string> channels;
	std::vector<std::string> keys;
	size_t i = 0;

	if (args.size() <= 1 || args.at(1).empty())
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}


	channels = parseArg(args.at(1));
	if (channels.size() > 2)
	{
		commandSender->sendMessage(NULL, "Too many channels specified");
		return false;
	}

	try
	{
		keys = parseArg(args.at(2));
	}
	catch(const std::exception& e)
	{
	}

	while (i < channels.size())
	{
		Channel *ch = getServer()->getChannel(channels.at(i));

		if (checkBadCharacters(channels.at(i)))
			commandSender->sendMessage(NULL, "Bad characters");
		else
		{
			if (ch == NULL)
			{
				try
				{
					getServer()->createChannel(channels.at(i), keys.at(i), false, 10);
				}
				catch(const std::exception& e)
				{
					getServer()->createChannel(channels.at(i), "", false, 10);
				}
				ch = getServer()->getChannel(channels.at(i));
			}
			if (ch->getUser(commandSender->getNickname()) == commandSender)
				commandSender->sendMessage(NULL, "You are already in this channel");
			else if (ch->getBanUser(commandSender->getNickname()) == commandSender)
				commandSender->sendMessage(NULL, "You are banned from this channel");
			else if (ch->getInvitedUser(commandSender->getNickname()) != commandSender && ch->isInviteOnly())
				commandSender->sendMessage(NULL, "You must be invited to join this channel");
			else if (ch->getUsers().size() == ch->getMaxSize())
				commandSender->sendMessage(NULL, "The target channel is full");
			else if ((keys.size() > i && ch->getPassword() != keys.at(i))
			|| (keys.size() == 0 && ch->getPassword() != ""))
				commandSender->sendMessage(NULL, "Wrong channel key");
			else
			{
				std::string tmp = ch->getName();
				tmp.append(" :");
				tmp.append(ch->getTopic());
				commandSender->sendMessage(NULL, tmp);
				tmp.clear();

				ch->removeInvitedUser(commandSender);

				tmp = commandSender->getNickname();
				tmp.append(" has joined the channel :").append(ch->getName()).append(".");
				ch->sendMessage(NULL, tmp);
				ch->addUser(commandSender);
				commandSender->addChannel(ch);
			}
		}
		i++;
	}
	return true;
}