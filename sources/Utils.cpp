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