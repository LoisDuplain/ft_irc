#include "commands/operator/ModeCommand.hpp"

ModeCommand::ModeCommand(Server *server)	:	ACommand(server, "MODE", true, true, true)
{
}
ModeCommand::~ModeCommand(void)
{
}

bool	ModeCommand::modeOp(Channel *ch, User *commandSender, std::vector<std::string> args)
{
	char	sign = args.at(2)[0];
	args.at(2).erase(args.at(2).begin());
	std::vector<char> flags;

	(void)ch;
	(void)sign;

	for (size_t i = 0; args.at(2)[i]; i++)
		flags.push_back(args.at(2)[i]);
	
	for (size_t i = 0; i < flags.size(); i++)
	{
		if (flags.at(i) == 'o')
		{

		}
		else if (flags.at(i) == 'p')
		{

		}
		else if (flags.at(i) == 's')
		{

		}
		else if (flags.at(i) == 'i')
		{

		}
		else if (flags.at(i) == 't')
		{

		}
		else if (flags.at(i) == 'n')
		{

		}
		else if (flags.at(i) == 'm')
		{

		}
		else if (flags.at(i) == 'l')
		{

		}
		else if (flags.at(i) == 'b')
		{

		}
		else if (flags.at(i) == 'v')
		{

		}
		else if (flags.at(i) == 'k')
		{

		}
		else
		{
			std::string tmp = "Flag invalid :";
			tmp.append(&flags.at(i)).append(".");
			commandSender->sendMessage(NULL, tmp);
			return false;
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