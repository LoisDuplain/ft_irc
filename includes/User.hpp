#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Channel.hpp"

class Channel;

class User
{
private:
	int 		_socket;

	std::string	_nickname;
	std::string	_username;
	std::string	_real_name;

	bool		_connected;
	bool		_authenticated;

	bool		_op;

	Channel		*_channel;
public:
	User(void);
	User(int socket);
	User &operator=(User const &rhs);
	~User();

	/* Messaging */
	void	sendMessage(User *from, std::string message)	const;

	int					getSocket(void)			const;
	const	std::string	getNickname(void)		const;
	const	std::string	getUsername(void)		const;
	const	std::string	getRealName(void)		const;
	bool				isConnected(void)		const;
	bool				isAuthenticated(void)	const;
	bool				isOp(void)				const;
	Channel				*getChannel(void)		const;

	/* Setter */
	bool				setChannel(Channel *channel);
};

std::ostream	&operator<<(std::ostream &ostream, User const &o);