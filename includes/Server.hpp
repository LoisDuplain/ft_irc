#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

class Server
{
private:
	int			_port;
	std::string	_password;

	std::map<int, User *>	_users;

	int					_master_socket;
	fd_set				_master_fds;
	fd_set				_read_fds;
	struct sockaddr_in	_address;
	int					_max_fd;
	
public:
	Server(void);
	Server(std::string port, std::string passord);
	Server &operator=(Server const &o);
	~Server();

	void	start(void);
	
	void	loop(void);
	void	readSocket(int socket);
	
	void	stop(void);

	bool	createUser(int user_socket);
	void	disconnectUser(User *user);

	void	sendMessageToUser(User &from, std::string to, std::string message)		const;	// TODO
	void	sendMessageToUser(User &from, User &to, std::string message)			const;	// TODO

	int					getPort(void)		const;
	const std::string	getPassword(void)	const;
};
