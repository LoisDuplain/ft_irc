#pragma once

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string>	tokenizeCommand(std::string commandLine);

bool checkBadCharacters(std::string s);

std::vector<std::string>	getChannelsNameInString(std::string string);
std::vector<std::string>	getUsersNameInString(std::string string);