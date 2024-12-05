#include "pch.h"
#include "request.h"

Request::Request(const std::string& reqString){
	parseRequest(reqString);
}

void Request::parseRequest(const std::string& reqString) {
	std::istringstream requestStream(reqString);
	std::string reqLine;

	if (std::getline(requestStream, reqLine)) {
		std::istringstream requestLineStream(reqLine);
		requestLineStream >> httpMethod >> url >> httpVersion;

		// parse query parameters
		size_t queryPos = url.find("?");
		if (queryPos != std::string::npos) {
			parseQueryParams(url.substr(queryPos + 1));
			url = url.substr(0, queryPos);
		}
	}
	else {
		throw std::runtime_error("Invalid request format");
	}

	while (std::getline(requestStream, reqLine) && reqLine != "\r") {
		size_t colonPos = reqLine.find(':');
		if (colonPos != std::string::npos) {
			std::string headerKey = reqLine.substr(0, colonPos);
			std::string headerValue = reqLine.substr(colonPos + 1);

			headerKey.erase(headerKey.find_last_not_of(" \t\n\r") + 1);
			headerKey.erase(0, headerKey.find_first_not_of(" \t\n\r"));

			headers.insert(std::make_pair(headerKey, headerValue));

			// parse cookie header
			if (headerKey == "Cookie") {
				parseCookies(headerValue);
			}
		}
	}

	// parse body
	if (std::getline(requestStream, reqLine)) {
		body = reqLine;
		std::string remainingLine;
		while (std::getline(requestStream, remainingLine)) {
			body += remainingLine;
		}
	}
	// Setting the content-length header
	headers["Content-Length"] = std::to_string(body.length());
	
}

void Request::parseQueryParams(const std::string& queryString) {
	std::istringstream queryParamsStream(queryString);
	std::string pair;
	while (std::getline(queryParamsStream, pair, '&')) {
		size_t equalPos = pair.find('=');
		if (equalPos != std::string::npos) {
			std::string key = pair.substr(0, equalPos);
			std::string value = pair.substr(equalPos + 1);

			queryParameters[key] = value;
		}
	}
}

void Request::parseCookies(const std::string& cookieString) {
	std::istringstream cookieStream(cookieString);
	std::string pair;

	while (std::getline(cookieStream, pair, ';')) {
		size_t equalPos = pair.find('=');
		if (equalPos != std::string::npos) {
			std::string key = pair.substr(0, equalPos);
			std::string value = pair.substr(equalPos + 1);

			key.erase(key.find_last_not_of(" \t\n\r") + 1);
			key.erase(0, key.find_first_not_of(" \t\n\r"));

			cookies[key] = value;
		}
	}
}

std::string Request::getHeader(const std::string& key) const {
	return headers.at(key);
}

std::string Request::getMethod() const {
	return httpMethod;
}

std::string Request::getUrl() const {
	return url;
}

std::string Request::getBody() const {
	return body;
}

std::string Request::getHttpVersion() const {
	return httpVersion;
}

std::string Request::getCookie(const std::string& key) const {
	return cookies.at(key);
}

std::string Request::getQueryParameter(const std::string& key) const {
	return queryParameters.at(key);
}