#include "pch.h"
#include "Response.h"
#include "nlohmann/json.hpp"

Response::Response(const std::string& version): version(version)
{
	headers["Content-Type"] = "text/plain";
	headers["Connection"] = "close";
	headers["Date"] = getCurrentDate();
}

Response& Response::status(unsigned short code) {
	statusCode = code;
	return *this;
}

Response& Response::set(const std::string& key, const std::string& value) {
	headers[key] = value;
	return *this;
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