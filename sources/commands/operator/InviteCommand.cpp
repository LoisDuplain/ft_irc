#include "commands/operator/InviteCommand.hpp"

InviteCommand::InviteCommand(Server *server)	:	ACommand(server, "TOPIC", true, true, true)
{
}
InviteCommand::~InviteCommand(void)
{
}

bool	InviteCommand::execute(User *commandSender, std::vector<std::string> args)
{

	if (args.size() <= 2 || args.at(1).empty())
	{
		commandSender->sendMessage(NULL, "Not enough parameters");
		return false;
	}

	User *usr = getServer()->getUser(args.at(1));
	Channel *ch = getServer()->getChannel(args.at(2));

	if (ch == NULL)
	{
		commandSender->sendMessage(NULL, "Channel not found");
		return false;
	}

	if (usr == NULL)
	{
		commandSender->sendMessage(NULL, "User not found");
		return false;
	}

	if (ch->getBanUser(usr->getNickname()) != NULL)
	{
		commandSender->sendMessage(NULL, "User was banned from this channel");
		return false;
	}

	ch->addInvitedUser(usr);

	std::string tmp = commandSender->getNickname();
	tmp.append(" change channel topic to :");
	tmp.append(ch->getTopic());
	tmp.append("\n");
	ch->sendMessage(NULL, tmp);
	return true;
}