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
		std::string msg;
		msg = ":" + user->getIp() + " " + RPL_WELCOME + " " + user->getNickname() + " :Welcome to our IRC server!\r\n";
		send(user->getSocket(), msg.c_str(), msg.size(), 0);

		msg = ":server " + std::string(RPL_MYINFO) + " " + user->getNickname() + " : ircserv 2.0\r\n";
		send(user->getSocket(), msg.c_str(), msg.size(), 0);
	}
}