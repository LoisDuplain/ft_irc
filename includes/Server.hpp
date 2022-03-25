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

#include "Utils.hpp"
#include "User.hpp"
#include "Channel.hpp"

#include "commands/CommandManager.hpp"
#include "commands/PassCommand.hpp"
#include "commands/NickCommand.hpp"

class Server
{
private:
	int			_port;
	std::string	_password;

	CommandManager	_commandManager;

	std::map<int, User *>				_users;
	std::map<std::string, Channel *>	_channels;

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

	/* Life cycle */
	void	start(void);
	void	loop(void);
	void	readSocket(int socket);
	void	stop(void);

	/* Command */
	void	registerCommands(void);
	void	executeCommand(User *commandSender, std::vector<std::string> args);

	/* User */
	bool	createUser(int user_socket);
	void	disconnectUser(User *user);
	User	*getUser(std::string nickname);
	User	*getUser(int socket);

	/* Channel */
	bool	createChannel(std::string name);
	bool	removeChannel(std::string name);
	Channel	*getChannel(std::string name);

	/* Getters */
	int					getPort(void)		const;
	const std::string	getPassword(void)	const;
};
