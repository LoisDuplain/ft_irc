#include "Server.hpp"

Server::Server(void)	:	_port(6667), _password(""), _master_socket(-1), _max_fd(-1)
{
}
Server::Server(std::string port, std::string password)	:	 _password(password), _master_socket(-1), _max_fd(-1)
{
	_port = stoi(port);
	if (_port < 0 || _port > 65535)
		throw std::out_of_range("");
}
Server &Server::operator=(Server const &o)
{
	_port = o._port;
	_password = o._password;
	_users = o._users;
	_master_socket = o._master_socket;
	return *this;
}
Server::~Server()
{
}

/* Life cycle */
void	Server::start(void)
{
	int opt = 1;

	_master_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (_master_socket <= 0)
		throw std::runtime_error("Socket creation failed.");
	std::cout << "Socket created." << std::endl;
	
	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Setting socket options failed.");
	std::cout << "Socket options set." << std::endl;

	_address.sin_family = AF_INET;  
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);
	
	if (bind(_master_socket, (struct sockaddr *) &_address, sizeof(_address)) < 0)
		throw std::runtime_error("Binding socket failed.");
	std::cout << "Socket binded." << std::endl;

	if (listen(_master_socket, 10) < 0)
		throw std::runtime_error("Listening socket failed.");
	std::cout << "Listening socket." << std::endl;
	
	FD_ZERO(&_master_fds);
	FD_ZERO(&_read_fds);

	FD_SET(_master_socket, &_master_fds);
	_max_fd = _master_socket;

	registerCommands();
}
void	Server::loop(void)
{
	std::cout << "Waiting for connections ..." << std::endl;

	int addrlen = sizeof(_address);
	while (true)
	{
		_read_fds = _master_fds;
		int activity = select(_max_fd + 1, &_read_fds, NULL, NULL, NULL);
		if ((activity < 0) && (errno != EINTR))
			std::cerr << "Select error" << std::endl;

		for (int fdi = 0; fdi <= _max_fd; fdi++)
		{
			if (FD_ISSET(fdi, &_read_fds))
			{
				if (fdi == _master_socket)
				{
					int user_socket = accept(_master_socket, (struct sockaddr *) &_address, (socklen_t *) &addrlen);
					createUser(user_socket, _address);
				}
				else
					readSocket(fdi);
			}
		}
	}
}
void	Server::readSocket(int socket)
{
	char	buff[512];
	int		readed_bytes;

	bzero(buff, sizeof(buff));
	readed_bytes = recv(socket, buff, sizeof(buff), 0);
	if (_users.count(socket) == 0)
		return;
	User *user = _users.at(socket);
	if (readed_bytes <= 0)
	{
		disconnectUser(user);
		return;
	}
	if (buff[readed_bytes - 1] == '\n')
		buff[readed_bytes - 1] = '\0';
	if (buff[readed_bytes - 2] == '\r')
		buff[readed_bytes - 2] = '\0';
	if (strlen(buff) == 0)
		return;
	std::cout << *user << ": " << buff << std::endl;
	executeCommand(user, tokenizeCommand(std::string(buff)));
}
void	Server::stop(void)
{
	_commandManager.unregisterCommands();

	std::map<int, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
		disconnectUser(it->second);
	close(_master_socket);
}

/* Command */
void	Server::registerCommands(void)
{
	_commandManager.registerCommand(new PassCommand(this));
	_commandManager.registerCommand(new NickCommand(this));
	_commandManager.registerCommand(new UserCommand(this));
	_commandManager.registerCommand(new JoinCommand(this));
	_commandManager.registerCommand(new TopicCommand(this));
	_commandManager.registerCommand(new KickCommand(this));
	_commandManager.registerCommand(new ModeCommand(this));
	_commandManager.registerCommand(new InviteCommand(this));
	_commandManager.registerCommand(new PrivMsgCommand(this));
}
void	Server::executeCommand(User *commandSender, std::vector<std::string> args)
{
	if (args.size() <= 0)
		return;

	if (args.at(0) == "PONG")
		return;

	ACommand *command = _commandManager.getCommand(args.at(0));
	if (command == NULL)
	{
		commandSender->sendMessage(NULL, "Unknown command: " + args.at(0));
		return;
	}
	command->preExecute(commandSender, args);
}

/* User */
bool	Server::createUser(int user_socket, sockaddr_in addr)
{
	if (_users.count(user_socket) >= 1)
		return false;
	User *newUser = new User(user_socket, inet_ntoa(addr.sin_addr));
	_users.insert(std::make_pair(user_socket, newUser));
	
	FD_SET(user_socket, &_master_fds);
	if (user_socket > _max_fd)
		_max_fd = user_socket;
	
	std::cout << "[+] User " << *newUser << " created." << std::endl;
	newUser->sendMessage(NULL, "Connection to server established");
	
	return true;
}
void	Server::disconnectUser(User *user)
{
	std::cout << "[-] User " << *user << " disconnected." << std::endl;
	if (_channels.size() > 0)
	{
		std::map<std::string, Channel *>::iterator it = _channels.begin();
		for ( ; it != _channels.end(); it++)
		{
			it->second->removeUser(user);
			it->second->removeBanUser(user);
			it->second->removeInvitedUser(user);
		}
	}
	_users.erase(user->getSocket());
	FD_CLR(user->getSocket(), &_master_fds);
	close(user->getSocket());
	delete user;
}
User	*Server::getUser(std::string nickname)
{
	std::map<int, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return NULL;
}
User	*Server::getUser(int socket)
{
	return _users.find(socket)->second;
}

/* Channel */
bool	Server::createChannel(std::string name, std::string password, bool isInviteOnly, size_t max_size)
{
	if (name.empty() || _channels.count(name) >= 1)
		return false;
	_channels.insert(std::make_pair(name, new Channel(name, password, isInviteOnly, max_size)));
	return true;
}
bool	Server::removeChannel(std::string name)
{
	Channel *channel = _channels.find(name)->second;
	if (name.empty() || channel == NULL)
		return false;
	if (_channels.erase(name) != 1)
		return false;
	delete channel; 
	return true;
}
Channel	*Server::getChannel(std::string name)
{
	return _channels.find(name)->second;
}

/* Getters */
int Server::getPort(void)	const
{
	return this->_port;
}
const std::string Server::getPassword(void)	const
{
	return this->_password;
}