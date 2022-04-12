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
		if (user->isOp())
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
		commandSender->sendError(ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");
		return false;
	}


	channels = parseArg(args.at(1));
	if (channels.size() > 10)
	{
		commandSender->sendError(ERR_TOOMANYCHANNELS, "JOIN " + channels.at(i) + " :" + "Too many channels specified");
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
			commandSender->sendError(ERR_ERRONEUSNICKNAME, "JOIN " + channels.at(i) + " :Bad characters");
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
				return true;
			else if (ch->getBannedUser(commandSender->getNickname()) == commandSender)
				commandSender->sendError(ERR_BANNEDFROMCHAN, "JOIN " + ch->getName() + " :" + "You are banned from this channel");
			else if (ch->getInvitedUser(commandSender->getNickname()) != commandSender && ch->isInviteOnly())
				commandSender->sendError(ERR_INVITEONLYCHAN, "JOIN " + ch->getName() + " :" + "You need to be invited to join this channel");
			else if (ch->getUsers().size() == ch->getMaxSize())
				commandSender->sendError(ERR_CHANNELISFULL, "JOIN " + ch->getName() + " :" + "Channel is full");
			else if ((keys.size() > i && ch->getPassword() != keys.at(i))
			|| (keys.size() == 0 && ch->getPassword() != ""))
				commandSender->sendError(ERR_BADCHANNELKEY, "JOIN " + ch->getName() + " :" + "Bad password");
			else
			{
				std::string msg = ":" + commandSender->getNickname() + "!" + commandSender->getUsername() + "@" + commandSender->getIp() + " JOIN " + ch->getName() + "\r\n";
				send(commandSender->getSocket(), msg.c_str(), msg.size(), 0);

				commandSender->sendError(RPL_TOPIC, commandSender->getNickname() + " " + ch->getName() + " :" + ch->getTopic());

				ch->removeInvitedUser(commandSender);
				ch->addUser(commandSender);
				commandSender->addChannel(ch);

				std::map<std::string, User*> users = ch->getUsers();
				for (std::map<std::string, User *>::iterator it = users.begin(); it != users.end(); it++)
				{
					User *user = it->second;
					user->sendError(RPL_NAMREPLY, user->getNickname() + " = " + ch->getName() + " :" + listClients(ch));
					user->sendError(RPL_ENDOFNAMES, user->getNickname() + " " + ch->getName() + " :End of NAMES list");
				}
				
			}
		}
		i++;
	}
	return true;
}