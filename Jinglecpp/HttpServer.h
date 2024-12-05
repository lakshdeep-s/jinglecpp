#pragma once
#include "pch.h"
#include "Response.h"
#include "request.h"

namespace Server 
{
	class HttpServer
	{
	private:
		int serverPort;
		SOCKET serverSocket;
		//std::unordered_map<std::string, std::function<void(const std::string&, Response& response)>> getRoutes;
		std::unordered_map<std::string, std::function<void(const std::string& requestString, Response& response)>> getRoutes;

		void initServerSocket();

		void processRequest(const std::string& request, Response& response) const;
	public:
		explicit HttpServer(int port);
		void startServer() const;

		void get(const std::string& route, std::function<void(const std::string& requestString, Response& response)> handler);

		~HttpServer();
	};
}

