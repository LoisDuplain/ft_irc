#include "commands/operator/InviteCommand.hpp"

InviteCommand::InviteCommand(Server *server)	:	ACommand(server, "INVITE", true, true, true)
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

	if (ch->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendError(ERR_CHANOPRIVSNEEDED, "INVITE " + args.at(1) + " :" + "You're not channel operator");
		return false;
	}

	if (usr == NULL)
	{
		commandSender->sendMessage(NULL, "User not found");
		return false;
	}

	if (ch->getBanUser(usr->getNickname()) == usr)
	{
		commandSender->sendMessage(NULL, "User was banned from this channel");
		return false;
	}

	if (!ch->isInviteOnly())
	{
		commandSender->sendMessage(NULL, "This chanel is not invitation only");
		return false;
	}

	if (ch->getInvitedUser(usr->getNickname()) == usr)
	{
		commandSender->sendMessage(NULL, "User already invited");
		return false;
	}

	ch->addInvitedUser(usr);

	std::string tmp = commandSender->getNickname();
	tmp.append(" invite you to the channel :");
	tmp.append(ch->getName());
	tmp.append("\n");
	usr->sendMessage(NULL, tmp);
	tmp.clear();
	tmp = "User was invited to the channel :";
	tmp.append(ch->getName()).append("\n");
	commandSender->sendMessage(NULL, tmp);
	return true;
}