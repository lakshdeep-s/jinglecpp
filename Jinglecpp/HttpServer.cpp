#include "pch.h"
#include "HttpServer.h"
#include "request.h"

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
		initServerSocket();
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

	void HttpServer::startServer() const{
		int listenResult = listen(serverSocket, SOMAXCONN);
		if (listenResult == SOCKET_ERROR) {
			throw std::runtime_error("Error listening on server socket: " + std::to_string(WSAGetLastError()) + "\n");
		}
		std::cout << "Server listening on port " << serverPort << "\n";

		SOCKADDR_IN clientAddr{};
		int clientAddrSize = sizeof(clientAddr);

		while (true) {
			SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
			if (clientSocket == INVALID_SOCKET) {
				throw std::runtime_error("Error in creating client socket: " + std::to_string(WSAGetLastError()));
			}
			std::cout << "Client Connected\n";

			char buffer[1024];
			int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesRead > 0) {
				std::string request(buffer, bytesRead);
				Response responseObject;

				processRequest(request, responseObject);
				std::string response = responseObject.getResponse();

				int responseSize = response.size();

				send(clientSocket, response.c_str(), responseSize, 0);
			}
			closesocket(clientSocket);
		}
	}

	void HttpServer::processRequest(const std::string& req, Response& response) const {
		/*std::string method, path;
		std::istringstream requestStream(request);
		requestStream >> method >> path;

		if (method == "GET" && getRoutes.find(path) != getRoutes.end()) {
			getRoutes.at(path)(request, response);
		}
		else {
			Response response = Response();
			response.status(404);
		}*/
		Request request(req);
		const std::string path = request.getUrl();
		const std::string method = request.getMethod();

		if (request.getMethod() == "GET" && getRoutes.find(request.getUrl()) != getRoutes.end()) {
			getRoutes.at(path)(req, response);
		}
		else {
			response.status(404);
		}
	}

	void HttpServer::get(const std::string& route, const std::function<void(const std::string& reqString, Response& response)> handler) {
		getRoutes[route] = handler;
	}
}