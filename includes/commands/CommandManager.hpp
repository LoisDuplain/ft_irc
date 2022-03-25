#pragma once

#include <map>
#include <string>

class ACommand;

class CommandManager
{
private:
	std::map<std::string, ACommand *>	_commands;
public:
	CommandManager(void);
	~CommandManager(void);

	bool	registerCommand(ACommand *command);
	void	unregisterCommands(void);

	ACommand	*getCommand(std::string label);

	const std::map<std::string, ACommand *>	getCommands(void)	const;
};

#include "ACommand.hpp"