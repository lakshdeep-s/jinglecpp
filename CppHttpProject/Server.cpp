#include "HttpServer.h"
#include "Response.h"
#include <iostream>
#include "nlohmann/json.hpp"

using namespace Server;

int main(void) {
	try
	{
		HttpServer server(8080);

		server.get("/health", [](const std::string& request, Response& response) {
			response.sendFile("./sample.txt");
		});

		server.startServer();
	}
	catch (const std::exception& e)
	{
		std::cout << "An Error Occured : " << e.what() << std::endl;
	}
	return 0;
}