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
	std::string	_ip;

	std::string	_nickname;
	std::string	_username;
	std::string	_real_name;

	bool		_connected;
	bool		_authenticated;

	bool		_op;

	std::map<std::string, Channel *>	_channels;
public:
	User(void);
	User(int socket, std::string ip);
	User &operator=(User const &rhs);
	~User();

	/* Messaging */
	void	sendMessage(User *from, std::string message)	const;

	/* Getter */
	int					getSocket(void)			const;
	std::string			getIp(void)				const;
	const	std::string	getNickname(void)		const;
	const	std::string	getUsername(void)		const;
	const	std::string	getRealName(void)		const;
	bool				isConnected(void)		const;
	bool				isAuthenticated(void)	const;
	bool				isOp(void)				const;
	std::map<std::string, Channel *> getChannels(void)		const;

	/* Setter */
	void				setNickname(std::string nickname);
	void				setUsername(std::string username);
	void				setRealName(std::string real_name);
	void				setConnected(bool state);
	void				setAuthenticated(bool state);
	void				setOp(bool state);
	bool				addChannel(Channel *channel);
};

std::ostream	&operator<<(std::ostream &ostream, User const &o);