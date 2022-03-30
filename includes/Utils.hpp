#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "Errors.hpp"

std::vector<std::string>	tokenizeCommand(std::string commandLine);

bool checkBadCharacters(std::string s);