#pragma once

#include <map>
#include <string>

#include "User.hpp"

class User;

class Channel
{
private:
	std::string						_name;
	std::string 					_password;
	std::map<std::string, User *>	_users;
	std::map<std::string, User *>	_ban_users;
	bool							_isInviteOnly;
	size_t							_max_size;

public:
	Channel(std::string name);
	Channel(std::string name, std::string password);
	Channel(std::string name, std::string password, bool isInviteOnly);
	Channel(std::string name, std::string password, bool isInviteOnly, size_t max_size);
	Channel &operator=(Channel const &rhs);
	~Channel();

	/* User */
	bool	addUser(User *user);
	bool	removeUser(User *user);
	User	*getUser(std::string name);

	bool	addBanUser(User *user);
	bool	removeBanUser(User *user);
	User	*getBanUser(std::string name);

	/* Messaging */
	void	sendMessage(User *from, std::string message);

	/* Getters */
	const	std::string				getName()		const;
	const	std::string				getPassword()	const;
	std::map<std::string, User *>	&getUsers();
	std::map<std::string, User *>	&getBanUsers();
	bool					isInviteOnly()	const;
	size_t					getMaxSize()	const;

	/* Setters */
	void							setPassword(std::string pass);

};
