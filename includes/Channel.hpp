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
	std::string						_topic;
	std::map<std::string, User *>	_users;
	std::map<std::string, User *>	_banned_users;
	std::map<std::string, User *>	_invited_users;
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

	bool	addBannedUser(User *user);
	bool	removeBannedUser(User *user);
	User	*getBannedUser(std::string name);

	bool	addInvitedUser(User *user);
	bool	removeInvitedUser(User *user);
	User	*getInvitedUser(std::string name);

	/* Messaging */
	void	sendMessage(User *from, std::string message);

	/* Getters */
	const	std::string				getName()		const;
	const	std::string				getPassword()	const;
	const	std::string				getTopic()		const;
	std::map<std::string, User *>	&getUsers();
	std::map<std::string, User *>	&getBannedUsers();
	std::map<std::string, User *>	&getInvitedUsers();
	bool							isInviteOnly()	const;
	size_t							getMaxSize()	const;

	/* Setters */
	void							setPassword(std::string pass);
	void							setTopic(std::string topic);
	void							setMaxSize(size_t n);
	void							setInviteOnly(bool b);

};
