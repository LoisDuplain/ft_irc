#include "commands/NickCommand.hpp"

NickCommand::NickCommand(Server *server)	:	ACommand(server, "NICK", true, false, false)
{
}
NickCommand::~NickCommand(void)
{
}

bool	NickCommand::execute(User *commandSender, std::vector<std::string> args)
{
	std::string nickname;

	nickname = args.at(1);
	if (nickname.at(0) == ':')
		nickname.erase(nickname.begin());
	if (args.size() <= 1 || nickname.empty())
	{
		commandSender->sendError(ERR_NONICKNAMEGIVEN, "NICK :Please specify a nickname");
		return false;
	}
	
	if (getServer()->getUser(nickname) != NULL)
	{
		commandSender->sendError(ERR_NICKNAMEINUSE, "NICK " + nickname + " :nickname already in use");
		return false;
	}

	if (checkBadCharacters(nickname))
	{
		commandSender->sendError(ERR_ERRONEUSNICKNAME, "NICK " + nickname + " :Bad characters");
		return false;
	}

	commandSender->setNickname(nickname);

	if (!commandSender->getNickname().empty() && !commandSender->getUsername().empty())
	{
		commandSender->setAuthenticated(true);
		if (commandSender->getNickname() == "op")
			commandSender->setOp(true);
	}
	return true;
}