#include "commands/operator/ModeCommand.hpp"

ModeCommand::ModeCommand(Server *server)	:	ACommand(server, "MODE", true, true, true)
{
}
ModeCommand::~ModeCommand(void)
{
}

bool	ModeCommand::modeOp(Channel *channel, User *commandSender, std::vector<std::string> args)
{
	char				sign;
	std::vector<char>	flags;

	if (channel->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendSTDPacket(ERR_CHANOPRIVSNEEDED, "MODE " + args.at(1) + " :You're not a channel operator");
		return false;
	}

	for (size_t i = 2; i < args.size(); i++)
	{
		sign = args.at(i)[0];
		args.at(i).erase(args.at(i).begin());

		if (sign != '+' && sign != '-')
			return false;
		
		flags.clear();
		for (size_t j = 0; args.at(i)[j]; j++)
			flags.push_back(args.at(i)[j]);

		for (size_t j = 0; j < flags.size(); j++)
		{
			User *usr;
			if (flags.at(j) == 'o')
			{
				try
				{
					usr = channel->getUser(args.at(++i));
				}
				catch(const std::exception& e)
				{
					commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
					return false;
				}
				
				if (usr == NULL)
					commandSender->sendSTDPacket(ERR_NOSUCHNICK, "MODE " + args.at(i) + " :No such nick/channel");
				else
				{
					if (sign == '+')
						channel->addOperatorUser(usr);
					else
						channel->removeOperatorUser(usr);
				}
			}
			else if (flags.at(j) == 'i')
			{
				if (sign == '+')
					channel->setInviteOnly(true);
				else
					channel->setInviteOnly(false);
			}
			else if (flags.at(j) == 't')
			{
				try
				{
					channel->setTopic(args.at(++i));
				}
				catch(const std::exception& e)
				{
					commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
					return false;
				}
			}
			else if (flags.at(j) == 'l')
			{
				try
				{
					channel->setMaxSize(atoi(args.at(++i).c_str()));
				}
				catch(const std::exception& e)
				{
					commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
					return false;
				}
			}
			else if (flags.at(j) == 'k')
			{
				try
				{
					channel->setPassword(args.at(++i));
				}
				catch(const std::exception& e)
				{
					commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
					return false;
				}
			}
			else
			{
				commandSender->sendSTDPacket(ERR_UMODEUNKNOWNFLAG, "MODE :Unknown MODE flag");
				return false;
			}
		}
	}
	return true;
}

bool	ModeCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() == 2)
		return false;
	if (args.size() <= 2 || args.at(1).empty())
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
		return false;
	}
	std::string channel_name = stringToLowerCase(args.at(1));
	Channel *channel = getServer()->getChannel(channel_name);
	if (channel == NULL)
	{
		commandSender->sendSTDPacket(ERR_NOSUCHCHANNEL, "MODE " + channel_name + " :Channel not found");
		return false;
	}

	return modeOp(channel, commandSender, args);
}