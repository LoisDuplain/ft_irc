#include "Channel.hpp"

Channel::Channel(std::string name)	:	_name(name), _password(""), _topic("Welcome to the channel.\n"), _isInviteOnly(false), _max_size(10)
{
}

Channel::Channel(std::string name, std::string password)	:	_name(name), _password(password), _topic("Welcome to the channel.\n"), _isInviteOnly(false), _max_size(10)
{
}

Channel::Channel(std::string name, std::string password, bool isInviteOnly)	:	_name(name), _password(password), _topic("Welcome to the channel.\n"), _isInviteOnly(isInviteOnly), _max_size(10)
{
}

Channel::Channel(std::string name, std::string password, bool isInviteOnly, size_t max_size)	:	_name(name), _password(password), _topic("Welcome to the channel.\n"), _isInviteOnly(isInviteOnly), _max_size(max_size)
{
}

Channel &Channel::operator=(Channel const &rhs)
{
	this->_name = rhs._name;
	this->_password = rhs._password;
	this->_isInviteOnly = rhs._isInviteOnly;
	this->_max_size = rhs._max_size;
	this->_ban_users = rhs._ban_users;
	this->_users = rhs._users;
	this->_topic = rhs._topic;
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
bool	Channel::addBanUser(User *user)
{
	if (user == NULL || _ban_users.find(user->getNickname()) != _ban_users.end())
		return false;
	_ban_users.insert(std::make_pair(user->getNickname(), user));
	return true;
}

bool	Channel::removeUser(User *user)
{
	if (user == NULL || _users.find(user->getNickname()) == _users.end())
		return false;
	return _users.erase(user->getNickname());
}
bool	Channel::removeBanUser(User *user)
{
	if (user == NULL || _ban_users.find(user->getNickname()) == _ban_users.end())
		return false;
	return _ban_users.erase(user->getNickname());
}

User	*Channel::getUser(std::string nickname)
{
	return _users.find(nickname)->second;
}
User	*Channel::getBanUser(std::string nickname)
{
	return _ban_users.find(nickname)->second;
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
std::map<std::string, User*> &Channel::getBanUsers()
{
	return _ban_users;
}
const	std::string	Channel::getName() const
{
	return _name;
}
const	std::string	Channel::getPassword() const
{
	return _password;
}
const	std::string	Channel::getTopic()	const
{
	return _topic;
}
bool Channel::isInviteOnly() const
{
	return _isInviteOnly;
}
size_t Channel::getMaxSize()	const
{
	return _max_size;
}

/* Setters */
void Channel::setPassword(std::string pass)
{
	_password = pass;
}
void Channel::setTopic(std::string topic)
{
	_topic = topic;
}
