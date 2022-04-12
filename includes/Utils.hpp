#pragma once

#include <vector>
#include <string>
#include <sstream>

class Channel;

std::vector<std::string>	tokenizeCommand(std::string commandLine);

bool checkBadCharacters(std::string s);
std::vector<std::string> parseArg(std::string s);

std::string	listClients(Channel channel);

#include "Channel.hpp"