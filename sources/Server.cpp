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
					createUser(user_socket);
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
	if (!_users.count(socket))
		return;
	User *user = _users.at(socket);
	if (readed_bytes <= 0)
	{
		disconnectUser(user);
		return;
	}
	buff[readed_bytes - 1] = '\0';
	if (strlen(buff) == 0)
		return;
	std::cout << *user << ": -" << buff << "-" << std::endl;
}

void	Server::stop(void)
{
	std::map<int, User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
		disconnectUser(it->second);
	close(_master_socket);
}

bool	Server::createUser(int user_socket)
{
	if (_users.count(user_socket))
		return (false);
	
	User *newUser = new User(user_socket);
	_users.insert(std::make_pair(user_socket, newUser));
	
	FD_SET(user_socket, &_master_fds);
	if (user_socket > _max_fd)
		_max_fd = user_socket;
	
	std::cout << "[+] User " << *newUser << " connected." << std::endl;
	newUser->sendMessage(NULL, "Connection to server established");
	
	return (true);
}
void	Server::disconnectUser(User *user)
{
	std::cout << "[-] User " << *user << " disconnected." << std::endl;
	_users.erase(user->getSocket());
	FD_CLR(user->getSocket(), &_master_fds);
	close(user->getSocket());
	delete user;
}

int Server::getPort(void)	const
{
	return this->_port;
}
const std::string Server::getPassword(void)	const
{
	return this->_password;
}