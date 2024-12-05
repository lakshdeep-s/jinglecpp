#include "pch.h"
#include "Response.h"
#include "nlohmann/json.hpp"

Response::Response(const std::string& version): version(version), statusCode(200), body("")
{
	headers["Content-Type"] = "text/plain";
	headers["Connection"] = "close";
	headers["Date"] = getCurrentDate();
	statusText = statusCodes.at(statusCode);
}

Response& Response::status(unsigned short code) {
	statusCode = code;
	statusText = statusCodes.at(statusCode);
	return *this;
}

Response& Response::setHeader(const std::string& key, const std::string& value) {
	headers[key] = value;
	return *this;
}

std::map<std::string, std::string> Response::getHeaders() const {
	return headers;
}

Response& Response::send(const std::string& data, const std::string& contentType) {
	if (data.empty()) {
		headers["Content-Length"] = "0";
		body = "";
	}
	else {
		headers["Content-Length"] = std::to_string(data.length());
		headers["Content-Type"] = contentType;
		body = data;
	}
	return *this;
}

/**
*@todo add enumerations for better support
*/
Response& Response::sendFile(const std::string& filePath) {
	try
	{
		if (filePath.empty()) {
			statusCode = 404;
			statusText = statusCodes.at(statusCode);
			return *this;
		}

		std::ifstream file(filePath, std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("The specified file could not be opened");
		}

		std::string extension = filePath.substr(filePath.find_last_of(".") + 1);
		if (extension == "jpg" || extension == "jpeg") {
			headers["Content-Type"] = "image/jpeg";
		}
		else if (extension == "txt") {
			headers["Content-Type"] = "text/plain";
		}
		else if (extension == "png") {
			headers["Content-Type"] = "image/png";
		}
		else if (extension == "html") {
			headers["Content-Type"] = "text/html";
		}
		else if (extension == "css") {
			headers["Content-Type"] = "text/css";
		}
		else if (extension == "js") {
			headers["Content-Type"] = "application/javascript";
		}
		else {
			headers["Content-Type"] = "application/octet-stream";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		body = buffer.str();
		return *this;
	}
	catch (const std::exception& e)
	{
		statusCode = 500;
		statusText = statusCodes.at(statusCode);
		body = "An error ocurred while sending the file: " + std::string(e.what());
	}
}

Response& Response::json(nlohmann::json& jsonObject) {
	body = jsonObject.dump(4);
	headers["Content-Type"] = "application/json";
	return *this;
}

const std::string Response::getResponse() const{
	std::string response;

	response = "HTTP/" + version + " " + std::to_string(statusCode) + " " + statusCodes.at(statusCode) + "\r\n";

	for (const auto& header : headers) {
		response += header.first + ": " + header.second + "\r\n";
	}

	response += "\r\n" + body;

	return response;
}

std::string Response::getCurrentDate() const{
	char buffer[100];
	time_t now = time(0);
	struct tm tm;
	gmtime_s(&tm, &now);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", &tm);
	return std::string(buffer);
}