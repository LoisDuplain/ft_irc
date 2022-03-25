#include "Utils.hpp"

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