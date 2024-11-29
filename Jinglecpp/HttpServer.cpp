#include "pch.h"
#include "HttpServer.h"

namespace Server
{
	// Initializing the HttpServer
	HttpServer::HttpServer(int port) : serverPort(port), serverSocket(INVALID_SOCKET)
	{
		WSADATA wsaData;
		int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (wsResult != 0) {
			throw std::runtime_error("WSAStartup Failed with error: " + std::to_string(wsResult));
		}
	}

	// Destructor, WSA Cleanup
	HttpServer::~HttpServer() {
		if (serverSocket != INVALID_SOCKET) {
			closesocket(serverSocket);
		}
		WSACleanup();
	}

	// Initialize the server socket
	void HttpServer::initServerSocket() {
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (serverSocket == INVALID_SOCKET) 
			throw std::runtime_error("Error in initializing server socket: " + std::to_string(WSAGetLastError()));

		SOCKADDR_IN serverAddr{};
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(serverPort);
		serverAddr.sin_addr.s_addr = INADDR_ANY;

		int bindResult = bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		if (bindResult == SOCKET_ERROR)
			throw std::runtime_error("Error in binding server socket: " + std::to_string(WSAGetLastError()));

		std::cout << "Server socket initialized and bound successfully.\n";
	}
}