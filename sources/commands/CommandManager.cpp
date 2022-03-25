#include "commands/CommandManager.hpp"

CommandManager::CommandManager(void)
{
}
CommandManager::~CommandManager(void)
{
}

bool	CommandManager::registerCommand(ACommand *command)
{
	std::string	label = command->getLabel();
	
	if (label.empty() || _commands.count(label) != 0)
		return false;
	
	_commands.insert(std::make_pair(label, command));
	std::cout << "Command " << label << " registered." << std::endl;
	return true;
}
void	CommandManager::unregisterCommands(void)
{
	std::map<std::string, ACommand *>::iterator	it;

	for (it = _commands.begin(); it != _commands.end(); it++)
	{
		ACommand *command = it->second;
		std::cout << "Command " << command->getLabel() << " registered." << std::endl;
		delete command;
	}
}

ACommand	*CommandManager::getCommand(std::string label)
{
	if (_commands.count(label) <= 0)
		return NULL;
	return _commands.at(label);
}

const std::map<std::string, ACommand *>	CommandManager::getCommands(void)	const
{
	return this->_commands;
}