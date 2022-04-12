#include "commands/operator/ModeCommand.hpp"

ModeCommand::ModeCommand(Server *server)	:	ACommand(server, "MODE", true, true, true)
{
}
ModeCommand::~ModeCommand(void)
{
}

bool	ModeCommand::modeOp(Channel *ch, User *commandSender, std::vector<std::string> args)
{
	char	sign;
	std::vector<char> flags;

	if (ch->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendError(ERR_CHANOPRIVSNEEDED, "MODE " + args.at(1) + " :" + "You're not channel operator");
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
					usr = ch->getUser(args.at(++i));
				}
				catch(const std::exception& e)
				{
					commandSender->sendMessage(NULL,  "Not enought parameter");
					return false;
				}
				
				if (usr == NULL)
					commandSender->sendMessage(NULL,  "User not found");
				else
				{
					if (sign == '+')
						ch->addOperatorUser(usr);
					else
						ch->removeOperatorUser(usr);
					commandSender->sendMessage(NULL,  "Operator attribute was changed");
				}
			}
			else if (flags.at(j) == 'p')
			{
				
			}
			else if (flags.at(j) == 's')
			{

			}
			else if (flags.at(j) == 'i')
			{
				if (sign == '+')
				{
					ch->setInviteOnly(true);
					commandSender->sendMessage(NULL,  "Channel are now in invite only");

				}
				else
				{
					ch->setInviteOnly(false);
					commandSender->sendMessage(NULL,  "Channel aren't now in invite only");
				}
			}
			else if (flags.at(j) == 't')
			{
				try
				{
					ch->setTopic(args.at(++i));
					commandSender->sendMessage(NULL,  "Channel topic was changed");
				}
				catch(const std::exception& e)
				{
					commandSender->sendMessage(NULL,  "Not enought parameter");
					return false;
				}
			}
			else if (flags.at(j) == 'n')
			{

			}
			else if (flags.at(j) == 'm')
			{

			}
			else if (flags.at(j) == 'l')
			{
				try
				{
					ch->setMaxSize(atoi(args.at(++i).c_str()));
					commandSender->sendMessage(NULL,  "Channel max size was changed");
				}
				catch(const std::exception& e)
				{
					commandSender->sendMessage(NULL,  "Not enought parameter");
					return false;
				}
			}
			else if (flags.at(j) == 'b')
			{

			}
			else if (flags.at(j) == 'v')
			{

			}
			else if (flags.at(j) == 'k')
			{
				try
				{
					ch->setPassword(args.at(++i));
					commandSender->sendMessage(NULL,  "Channel password was changed");
				}
				catch(const std::exception& e)
				{
					commandSender->sendMessage(NULL,  "Not enought parameter");
					return false;
				}
			}
			else
			{
				std::string tmp = "Flag invalid :";
				tmp.append(&flags.at(j)).append(".");
				commandSender->sendMessage(NULL, tmp);
				return false;
			}
		}
	}
	return true;
}

bool	ModeCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 2 || args.at(1).empty())
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}

	Channel *ch = getServer()->getChannel(args.at(1));

	if (ch == NULL)
	{
		commandSender->sendMessage(NULL, "Channel not found");
		return false;
	}

	return modeOp(ch, commandSender, args);
}