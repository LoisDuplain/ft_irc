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
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
		return false;
	}

	User *usr = getServer()->getUser(args.at(1));
	Channel *ch = getServer()->getChannel(args.at(2));
	if (ch == NULL)
	{
		commandSender->sendSTDPacket(ERR_NOSUCHCHANNEL, "INVITE " + args.at(2) + " :Channel not found");
		return false;
	}

	if (ch->getUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendSTDPacket(ERR_NOTONCHANNEL, "INVITE " + ch->getName() + " :" + "You're not on that channel");
		return false;
	}

	if (ch->getOperatorUser(commandSender->getNickname()) != commandSender)
	{
		commandSender->sendSTDPacket(ERR_CHANOPRIVSNEEDED, "INVITE " + args.at(1) + " :" + "You're not channel operator");
		return false;
	}

	if (usr == NULL)
	{
		commandSender->sendSTDPacket(ERR_NOSUCHNICK, "INVITE " + args.at(1) + " :No such nick/channel");
		return false;
	}

	if (ch->getUser(usr->getNickname()) == usr)
	{

		commandSender->sendSTDPacket(ERR_USERONCHANNEL, "INVITE " + usr->getNickname() + " " + ch->getName() + " :is already on channel");
		return false;
	}

	ch->addInvitedUser(usr);

	commandSender->sendSTDPacket(RPL_INVITING, ch->getName() + " " + commandSender->getNickname() + " " + ch->getName());
	
	return true;
}