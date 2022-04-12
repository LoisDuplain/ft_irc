#include "User.hpp"

User::User(void)	:	_socket(-1), _connected(false), _authenticated(false), _op(false)
{
}
User::User(int socket, std::string ip)	:	_socket(socket), _ip(ip), _connected(false), _authenticated(false), _op(false)
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

	new_message.append(":");
	if (from != NULL)
		new_message.append(from->getNickname()).append(" PRIVMSG ");
	else
		new_message.append("SERVER NOTICE ");
	
	if (_nickname.empty())
		new_message.append("*");
	else
		new_message.append(_nickname);
	
	new_message.append(" :");
	new_message.append(message);
	new_message.append("\r\n\0");
	send(_socket, new_message.c_str(), new_message.size(), 0);
	std::cout << "> " << new_message << std::endl;
}

void	User::sendError(int error, std::string message)	const
{
	std::string	new_message = ":server " + std::to_string(error) + " " + message + "\r\n\0";

	send(_socket, new_message.c_str(), new_message.size(), 0);
	std::cout << "> " << new_message << std::endl;
}

/* Getter */
int					User::getSocket(void)		const
{
	return this->_socket;
}
std::string			User::getIp(void)			const
{
	return this->_ip;
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
std::map<std::string, Channel *> User::getChannels(void)		const
{
	return this->_channels;
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
bool				User::addChannel(Channel *channel)
{
	if (channel == NULL || _channels.count(channel->getName()) >= 1)
		return false;
	_channels.insert(std::make_pair(channel->getName(), channel));
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