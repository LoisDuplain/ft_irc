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
	Server server;
	try
	{
		server = Server(string(argv[1]), string(argv[2]));
		server.start();
	}
	catch (invalid_argument const& ex)
	{
		cerr << "Wrong port format." << endl;
	}
	catch (out_of_range const& ex)
	{
		cerr << "Wrong port. Must be contained between 0 and 65535." << endl;
	}
	catch (exception const& ex)
	{
		cerr << ex.what() << endl;
	}
	server.loop();
	server.stop();
	return (0);
}