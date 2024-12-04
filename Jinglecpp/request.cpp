#include "pch.h"
#include "request.h"

Request::Request(const std::string& reqString) {

}

void Request::parseRequest(const std::string& reqString) {

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