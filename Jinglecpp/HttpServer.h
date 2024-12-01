#pragma once
#include "pch.h"

namespace Server 
{
	class HttpServer
	{
	private:
		int serverPort;
		SOCKET serverSocket;
		std::unordered_map<std::string, std::function<void(const std::string&, std::string&)>> getRoutes;

		void initServerSocket();

		void processRequest(const std::string& request, std::string& response) const;
	public:
		explicit HttpServer(int port);
		void startServer() const;

		/*using Handler = std::function<void(const std::string&, const std::string&)>;*/
		void get(const std::string& route, std::function<void(const std::string&, std::string&)> handler);

		~HttpServer();
	};
}

