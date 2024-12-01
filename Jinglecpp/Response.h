#include "pch.h"
#pragma once
#include "nlohmann/json.hpp"

class Response
{
private:
	std::string version;
	unsigned short statusCode;
	std::string statusText;
	std::string body;
	std::map<std::string, std::string>headers;
	std::map<unsigned short, std::string>statusCodes = {
		{200,"OK"},
		{400,"Bad Request"},
		{404,"Not Found"},
		{500,"Internal Server Error"}
	};

public:
	Response(const std::string& version="1.1");

	Response& status(unsigned short statusCode);

	Response& set(const std::string& key, const std::string& value);

	Response& json(nlohmann::json& jsonObject);

	const std::string getResponse() const;

	std::string getCurrentDate() const;
};

