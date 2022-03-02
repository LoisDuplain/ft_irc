#include <iostream>

#include "Server.hpp"

using namespace std;

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Usage: ./ircserver <port> <password>" << endl;
		return (1);
	}
	Server server = Server(string(argv[1]), string(argv[2]));
	cout << "Starting server on port " << server.getPort() << ". (password: " << server.getPassword() << ")" << endl;
	return (0);
}