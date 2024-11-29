#pragma once
#include "pch.h"

namespace Server 
{
	class HttpServer
	{
	private:
		int serverPort;
		SOCKET serverSocket;

		void initServerSocket();
	public:
		explicit HttpServer(int port);
		~HttpServer();
	};
}

