#include <iostream>

#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ircserver <port> <password>" << std::endl;
		return (1);
	}
	Server server;
	try
	{
		server = Server(std::string(argv[1]), std::string(argv[2]));
		server.start();
	}
	catch (std::invalid_argument const& ex)
	{
		std::cerr << "Wrong port format." << std::endl;
	}
	catch (std::out_of_range const& ex)
	{
		std::cerr << "Wrong port. Must be contained between 0 and 65535." << std::endl;
	}
	catch (std::exception const& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	server.loop();
	server.stop();
	return (0);
}