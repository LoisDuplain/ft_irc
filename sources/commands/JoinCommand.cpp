#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand(Server *server)	:	ACommand(server, "JOIN", true, true, false)
{
}
JoinCommand::~JoinCommand(void)
{
}

std::vector<std::string> parseArg(std::string s)
{
	std::string delimiter = ",";
	std::vector<std::string> res;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
    	token = s.substr(0, pos);
		std::cout << token << std::endl;
		res.push_back(token);
    	s.erase(0, pos + delimiter.length());
	}
	res.push_back(s);
	return res;
}

bool	JoinCommand::execute(User *commandSender, std::vector<std::string> args)
{
	std::vector<std::string> channels;
	std::vector<std::string> keys;
	size_t i = 0;

	if (args.size() <= 1 || args.at(1).empty())
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NEEDMOREPARAMS, "JOIN", ""));
		return false;
	}
    
	channels = parseArg(args.at(1));
	try
	{
		keys = parseArg(args.at(2));
	}
	catch(const std::exception& e)
	{
		
	}
	

	if (channels.size() > 2)
	{
		commandSender->sendMessage(NULL, replaceErrorArgs(ERR_TOOMANYCHANNELS, "", ""));
		return false;
	}

	while (i < channels.size())
	{
		Channel *ch = getServer()->getChannel(channels.at(i));
		if (ch == NULL)
			commandSender->sendMessage(NULL, replaceErrorArgs(ERR_NOSUCHCHANNEL, channels.at(i), ""));
		else if (ch->getBanUser(commandSender->getNickname()) == commandSender)
			commandSender->sendMessage(NULL, replaceErrorArgs(ERR_BANNEDFROMCHAN, channels.at(i), ""));
		else if (ch->isInviteOnly())
			commandSender->sendMessage(NULL, replaceErrorArgs(ERR_INVITEONLYCHAN, channels.at(i), ""));
		else if (ch->getUsers().size() == ch->getMaxSize())
			commandSender->sendMessage(NULL, replaceErrorArgs(ERR_CHANNELISFULL, channels.at(i), ""));
		else if ((keys.size() > 0 && ch->getPassword() != keys.at(i)) || (keys.size() == 0 && ch->getPassword() != ""))
			commandSender->sendMessage(NULL, replaceErrorArgs(ERR_BADCHANNELKEY, channels.at(i), ""));
		else if (ch->getUser(commandSender->getNickname()) != commandSender)
		{
			ch->addUser(commandSender);
			commandSender->addChannel(ch);
			commandSender->sendMessage(NULL, "You are now logged into channel :" + channels.at(i));
		}
		i++;
	}

	return true;
}