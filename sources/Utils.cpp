#include "Utils.hpp"

#define BAD_CHARACTERS "{}|[]\\"

std::vector<std::string>	tokenizeCommand(std::string commandLine)
{
	std::vector<std::string> args;
	
	std::string arg;
	std::istringstream	commandStream(commandLine);
	while (std::getline(commandStream, arg, ' '))
	{
		args.push_back(arg);
	}
	return args;
}

bool checkBadCharacters(std::string s)
{
	size_t i = 0;
	size_t j = 0;

	while (i < s.size())
	{
		j = 0;
		while (BAD_CHARACTERS[j++])
		{
			if (s[i] == BAD_CHARACTERS[j])
				return true;
		}
		i++;
	}
	return false;
}

std::vector<std::string> parseArg(std::string s)
{
	std::string delimiter = ",";
	std::vector<std::string> res;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
    	token = s.substr(0, pos);
		res.push_back(token);
    	s.erase(0, pos + delimiter.length());
	}
	res.push_back(s);
	return res;
}

std::string	listClients(Channel channel)
{
	std::string result;
	
	std::map<std::string, User*> users = channel.getUsers();
	for (std::map<std::string, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		User *user = it->second;
		if (channel.getOperatorUser(user->getNickname()) == user)
			result += "@";
		result += user->getNickname() + " ";
	}
	result.pop_back();
	return result;
}

void connectToServer(User *user)
{
	if (!user->getNickname().empty() && !user->getUsername().empty())
	{
		user->setAuthenticated(true);
		
		user->sendSTDPacket(RPL_WELCOME, user->getNickname() + " :Welcome to our irc server !");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :It has been created by jcambaki (Jeremie Cambakidis) and lduplain (Lois Duplain)");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :This server is useless");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :|    _    _       _       _____ _____   _____ ");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :| (_) |  | |     | |     |_   _|  __ \\ / ____|");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :|  _| |__| | __ _| |_ ___  | | | |__) | |     ");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :| | |  __  |/ _` | __/ _ \\ | | |  _  /| |     ");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :| | | |  | | (_| | ||  __/_| |_| | \\ \\| |____ ");
		user->sendSTDPacket(RPL_MYINFO, user->getNickname() + " :| |_|_|  |_|\\__,_|\\__\\___|_____|_|  \\_\\\\_____|");
	}
}

std::string stringToLowerCase(std::string s)
{
	std::string tmp = s;
	std::string::iterator it = tmp.begin();
	for ( ; it < tmp.end(); it++)
	{
		if (std::isalnum(*it))
			*it = std::tolower(*it);		
	}
	return tmp;
}