#pragma once

#include <map>
#include <string>

#include "User.hpp"

class User;

class Channel
{
private:
	std::string	_name;
	
	std::map<std::string, User *>	_users;
public:
	Channel(std::string name);
	Channel &operator=(Channel const &rhs);
	~Channel();

	/* User */
	bool	addUser(User *user);
	bool	removeUser(User *user);
	User	*getUser(std::string name);

	/* Messaging */
	void	sendMessage(User *from, std::string message);

	/* Getters */
	const	std::string				getName()	const;	
	std::map<std::string, User *>	&getUsers();
};
