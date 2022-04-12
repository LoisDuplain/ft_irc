#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand(Server *server)	:	ACommand(server, "JOIN", true, true, false)
{
}
JoinCommand::~JoinCommand(void)
{
}

std::string	listClients(Channel *channel)
{
	std::string result;
	
	std::map<std::string, User*> users = channel->getUsers();
	for (std::map<std::string, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		User *user = it->second;
		if (channel->getOperatorUser(user->getNickname()) == user)
			result += "@";
		result += user->getNickname() + " ";
	}
	result.pop_back();
	return result;
}

bool	JoinCommand::execute(User *commandSender, std::vector<std::string> args)
{
	std::vector<std::string> channels;
	std::vector<std::string> keys;
	size_t i = 0;

	if (args.size() <= 1 || args.at(1).empty())
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
		return false;
	}


	channels = parseArg(args.at(1));
	if (channels.size() > 10)
	{
		commandSender->sendSTDPacket(ERR_TOOMANYCHANNELS, "JOIN " + channels.at(i) + " :" + "Too many channels specified");
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
		Channel *channel = getServer()->getChannel(channels.at(i));

		if (checkBadCharacters(channels.at(i)))
			commandSender->sendSTDPacket(ERR_ERRONEUSNICKNAME, "JOIN " + channels.at(i) + " :Bad characters");
		else
		{
			if (channel == NULL)
			{
				try
				{
					getServer()->createChannel(channels.at(i), keys.at(i), false, 10);
				}
				catch(const std::exception& e)
				{
					getServer()->createChannel(channels.at(i), "", false, 10);
				}
				channel = getServer()->getChannel(channels.at(i));
				channel->addOperatorUser(commandSender);
			}
			if (channel->getUser(commandSender->getNickname()) == commandSender)
				return true;
			else if (channel->getBannedUser(commandSender->getNickname()) == commandSender)
				commandSender->sendSTDPacket(ERR_BANNEDFROMCHAN, "JOIN " + channel->getName() + " :You are banned from this channel");
			else if (channel->getInvitedUser(commandSender->getNickname()) != commandSender && channel->isInviteOnly())
				commandSender->sendSTDPacket(ERR_INVITEONLYCHAN, "JOIN " + channel->getName() + " :You need to be invited to join this channel");
			else if (channel->getUsers().size() == channel->getMaxSize())
				commandSender->sendSTDPacket(ERR_CHANNELISFULL, "JOIN " + channel->getName() + " :Channel is full");
			else if ((keys.size() > i && channel->getPassword() != keys.at(i))
			|| (keys.size() == 0 && channel->getPassword() != ""))
				commandSender->sendSTDPacket(ERR_BADCHANNELKEY, "JOIN " + channel->getName() + " :Bad password");
			else
			{
				channel->removeInvitedUser(commandSender);
				channel->addUser(commandSender);
				commandSender->addChannel(channel);

				commandSender->sendSTDPacket(RPL_TOPIC, commandSender->getNickname() + " " + channel->getName() + " :" + channel->getTopic());
				channel->sendRefreshedUserList();
			}
		}
		i++;
	}
	return true;
}