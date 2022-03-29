#include "Errors.hpp"

std::string replaceErrorArgs(std::string err, std::string arg1, std::string arg2)
{
	size_t i = 0;
	size_t start = 0;
	size_t end = 0;
	std::string tmp = err;

	while ((start = tmp.find('<')) != tmp.npos && (end = tmp.find('>')) != tmp.npos)
	{
		tmp.erase(start, end - start + 1);
		if (i == 0)
			tmp.insert(start, arg1);
		else
			tmp.insert(start, arg2);
		i++;
	}
	return tmp;
}