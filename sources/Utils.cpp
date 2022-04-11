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
