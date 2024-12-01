#include "HttpServer.h"
#include <iostream>
using namespace Server;

int main(void) {
	try
	{
		HttpServer server(8080);

		server.get("/health", [](const std::string& request, std::string& response) {
			response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHealthy";
			});

		server.startServer();
	}
	catch (const std::exception& e)
	{
		std::cout << "An Error Occured : " << e.what() << std::endl;
	}
	return 0;
}