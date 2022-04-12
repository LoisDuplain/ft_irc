#pragma once

#include <vector>
#include <string>
#include <sstream>

class Channel;
class User;

std::vector<std::string>	tokenizeCommand(std::string commandLine);

bool checkBadCharacters(std::string s);
std::vector<std::string> parseArg(std::string s);

std::string	listClients(Channel channel);

void connectToServer(User *user);

#include "Channel.hpp"
#include "User.hpp"