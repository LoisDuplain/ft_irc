#include "User.hpp"

User::User(void)	:	_socket(-1), _connected(false), _authenticated(false), _op(false)
{
}
User::User(int socket)	:	_socket(socket), _connected(false), _authenticated(false), _op(false)
{
}
User &User::operator=(User const &rhs)
{
	this->_socket = rhs._socket;
	this->_nickname = rhs._nickname;
	this->_username = rhs._username;
	this->_real_name = rhs._real_name;
	this->_connected = rhs._connected;
	this->_authenticated = rhs._authenticated;
	this->_op = rhs._op;
	return *this;
}
User::~User()
{
}

/* Messaging */
void	User::sendMessage(User *from, std::string message)	const
{
	std::string	new_message;

	if (_nickname.empty())
		return;

	if (from != NULL)
		new_message.append(from->getNickname()).append(": ");
	else
		new_message.append(":SERVER NOTICE ");
	new_message.append(_nickname);
	new_message.append(" :");
	new_message.append(message);
	new_message.append("\n\0");
	send(_socket, new_message.c_str(), new_message.size(), 0);
}

/* Getter */
int					User::getSocket(void)		const
{
	return this->_socket;
}
const	std::string	User::getNickname(void)		const
{
	return this->_nickname;
}
const	std::string	User::getUsername(void)		const
{
	return this->_username;
}
const	std::string	User::getRealName(void)		const
{
	return this->_real_name;
}
bool				User::isConnected(void)		const
{
	return this->_connected;
}
bool				User::isAuthenticated(void)	const
{
	return this->_authenticated;
}
bool				User::isOp(void)			const
{
	return this->_op;
}
Channel				*User::getChannel(void)		const
{
	return this->_channel;
}

/* Setter */
void				User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}
void				User::setUsername(std::string username)
{
	this->_username = username;
}
void				User::setRealName(std::string real_name)
{
	this->_real_name = real_name;
}
void				User::setConnected(bool state)
{
	this->_connected = state;
}
void				User::setAuthenticated(bool state)
{
	this->_authenticated = state;
}
void				User::setOp(bool state)
{
	this->_op = state;
}
bool				User::setChannel(Channel *channel)
{
	if (channel == NULL || channel == _channel)
		return false;
	if (_channel != NULL && !_channel->removeUser(this))
		return false;
	_channel = channel;
	if (!_channel->addUser(this))
		return false;
	return true;
}

/* Print */
std::ostream	&operator<<(std::ostream &ostream, User const &o)
{
	ostream
	<< "\""
	<< ((o.getNickname() == "") ? "NULL" : o.getNickname())
	<< "\""
	<< " (sckt: "
	<< o.getSocket()
	<< ")";
	return ostream;
}