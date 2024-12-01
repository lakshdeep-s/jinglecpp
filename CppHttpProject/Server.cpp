#include "HttpServer.h"
#include "Response.h"
#include <iostream>
using namespace Server;

int main(void) {
	try
	{
		HttpServer server(8080);

		server.get("/health", [](const std::string& request, Response& response) {
			response.status(200);
			});

		server.startServer();
	}
	catch (const std::exception& e)
	{
		std::cout << "An Error Occured : " << e.what() << std::endl;
	}
	return 0;
}