#include "commands/UserCommand.hpp"

UserCommand::UserCommand(Server *server)	:	ACommand(server, "USER", true, false, false)
{
}
UserCommand::~UserCommand(void)
{
}

bool	UserCommand::execute(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 4 || args.at(4)[1] == '\0')
	{
		commandSender->sendSTDPacket(ERR_NEEDMOREPARAMS, "USER :Not enough parameters");
		return false;
	}

	if (!commandSender->getUsername().empty())
	{
		commandSender->sendSTDPacket(ERR_ALREADYREGISTRED, "USER :You may not reregister");
		return false;
	}
	
	commandSender->setUsername(args.at(1));

	std::string real_name = args.at(4);
	if (real_name.at(0) == ':')
		real_name.erase(real_name.begin());
	for (size_t i = 5; i < args.size(); i++)
		real_name.append(" ").append(args.at(i));
	commandSender->setRealName(real_name);

	if (!commandSender->getNickname().empty() && !commandSender->getUsername().empty())
	{
		commandSender->setAuthenticated(true);
		std::string msg;
		msg = ":" + commandSender->getIp() + " " + RPL_WELCOME + " " + commandSender->getNickname() + " :Welcome to our IRC server!\r\n";
		send(commandSender->getSocket(), msg.c_str(), msg.size(), 0);

		msg = ":server " + std::string(RPL_MYINFO) + " " + commandSender->getNickname() + " : ircserv 2.0\r\n";
		send(commandSender->getSocket(), msg.c_str(), msg.size(), 0);
	}
	return true;
}