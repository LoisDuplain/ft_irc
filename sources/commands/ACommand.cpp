#include "commands/ACommand.hpp"

ACommand::ACommand(Server *server, std::string label, bool needConnected, bool needAuthenticated, bool needOp)	:	_server(server), _label(label), _needConnected(needConnected), _needAuthenticated(needAuthenticated), _needOp(needOp)
{
}
ACommand::~ACommand(void)
{
}

bool	ACommand::preExecute(User *commandSender, std::vector<std::string> args)
{
	if (_needConnected && !commandSender->isConnected())
	{
		std::cout << *commandSender << " is trying to execute a command who needs to be connected." << std::endl;
		commandSender->sendSTDPacket(ERR_NOLOGIN, commandSender->getNickname() + " :" + "User not logged in");
		return false;
	}
	if (_needAuthenticated && !commandSender->isAuthenticated())
	{
		std::cout << *commandSender << " is trying to execute a command who needs to be authenticated." << std::endl;
		commandSender->sendSTDPacket(ERR_NOTREGISTERED, ":You have not registered");
		return false;
	}
	return execute(commandSender, args);
}
bool	ACommand::execute(User *commandSender, std::vector<std::string> args)
{
	(void)commandSender;
	(void)args;
	return false;
}

Server		*ACommand::getServer()					const
{
	return this->_server;
}
const	std::string	ACommand::getLabel()			const
{
	return this->_label;
}
bool		ACommand::needConnected()		const
{
	return this->_needConnected;
}
bool		ACommand::needAuthenticated()	const
{
	return this->_needAuthenticated;
}
bool		ACommand::needOp()				const
{
	return this->_needOp;
}