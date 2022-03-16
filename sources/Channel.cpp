#include "Channel.hpp"

Channel::Channel(std::string name)	:	_name(name)
{
}
Channel &Channel::operator=(Channel const &rhs)
{
	this->_name = rhs._name;
	this->_users = rhs._users;
	return *this;
}
Channel::~Channel(void)
{
}

/* User */
bool	Channel::addUser(User *user)
{
	if (user == NULL || _users.find(user->getNickname()) != _users.end())
		return false;
	_users.insert(std::make_pair(user->getNickname(), user));
	return true;
}
bool	Channel::removeUser(User *user)
{
	if (user == NULL || _users.find(user->getNickname()) == _users.end())
		return false;
	return _users.erase(user->getNickname());
}
User	*Channel::getUser(std::string nickname)
{
	return _users.find(nickname)->second;
}

/* Messaging */
void	Channel::sendMessage(User *from, std::string message)
{
	std::map<std::string, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		User *to = it->second;
		to->sendMessage(from, message);
	}
}

/* Getters */
std::map<std::string, User*> &Channel::getUsers()
{
	return _users;
}
const	std::string	Channel::getName() const
{
	return _name;
}