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
	this->_banned_users = rhs._banned_users;
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
bool	Channel::addBannedUser(User *user)
{
	if (user == NULL || _banned_users.find(user->getNickname()) != _banned_users.end())
		return false;
	_banned_users.insert(std::make_pair(user->getNickname(), user));
	return true;
}
bool	Channel::addInvitedUser(User *user)
{
	if (user == NULL || _invited_users.find(user->getNickname()) != _invited_users.end())
		return false;
	_invited_users.insert(std::make_pair(user->getNickname(), user));
	return true;
}
bool	Channel::addOperatorUser(User *user)
{
	if (user == NULL || _operator_users.find(user->getNickname()) != _operator_users.end())
		return false;
	_operator_users.insert(std::make_pair(user->getNickname(), user));
	return true;
}

bool	Channel::removeUser(User *user)
{
	if (user == NULL || _users.find(user->getNickname()) == _users.end())
		return false;
	return _users.erase(user->getNickname());
}
bool	Channel::removeBannedUser(User *user)
{
	if (user == NULL || _banned_users.find(user->getNickname()) == _banned_users.end())
		return false;
	return _banned_users.erase(user->getNickname());
}
bool	Channel::removeInvitedUser(User *user)
{
	if (user == NULL || _invited_users.find(user->getNickname()) == _invited_users.end())
		return false;
	return _invited_users.erase(user->getNickname());
}
bool	Channel::removeOperatorUser(User *user)
{
	if (user == NULL || _operator_users.find(user->getNickname()) == _operator_users.end())
		return false;
	return _operator_users.erase(user->getNickname());
}

User	*Channel::getUser(std::string nickname)
{
	return _users.find(nickname)->second;
}
User	*Channel::getBanUser(std::string nickname)
{
	return _banned_users.find(nickname)->second;
}
User	*Channel::getInvitedUser(std::string nickname)
{
	return _invited_users.find(nickname)->second;
}
User	*Channel::getOperatorUser(std::string nickname)
{
	return _operator_users.find(nickname)->second;
}

/* Messaging */
void	Channel::sendMessage(User *from, std::string message)
{
	std::map<std::string, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		User *to = it->second;
		if (to != from)
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
	return _banned_users;
}
std::map<std::string, User *>	&Channel::getInvitedUsers()
{
	return _invited_users;
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

void Channel::setInviteOnly(bool b)
{
	_isInviteOnly = b;
}

void Channel::setMaxSize(size_t n)
{
	_max_size = n;
}