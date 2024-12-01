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
			nlohmann::json jsonResponse = "{\"status\":true, \"message\":\"Server is up and running\"}"_json;
			response.status(200).json(jsonResponse);
		});

		

		server.startServer();
	}
	catch (const std::exception& e)
	{
		std::cout << "An Error Occured : " << e.what() << std::endl;
	}
	return 0;
}