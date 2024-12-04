/**
* @file request.h
* @brief Contains declarations for member methods and variables for the Request class
* @author Lakshdeep Singh \link https://www.github.com/lakshdeep-s
*/
#include "pch.h"
#pragma once

/**
* @class Request
* @brief Request class for handling HTTP requests
*/
class Request
{	
private:
	/**
	* @var version
	* @breif the HTTP version of the request (default: "1.1").
	*/
	std::string httpVersion;
		
	/**
	* @var method
	* @breif the HTTP method of the request
	*/
	std::string httpMethod;

	/**
	* @var url
	* @breif the URL of the request
	*/
	std::string url;

	/**
	* @var headers
	* @breif the headers of the request
	*/
	std::unordered_map<const std::string&, const std::string&>headers;
	
	/**
	* @var queryParameters
	* @breif the query parameters of the request
	*/
	std::unordered_map<const std::string&, const std::string&>queryParameters;
		
	/**
	* @var body
	* @breif the body of the request
	*/
	std::string body;

	/**
	* @var cookies
	* @breif the cookies of the request
	*/
	std::unordered_map<const std::string&, const std::string&>cookies;




public:
	/**
	* @brief Default constructor
	* @param reqString The request string
	*/
	Request(const std::string& reqString);

	/**
	* @breif gets the header value of the given key
	* @param key The key of the header
	* @return The value of the header
	*/
	std::string getHeader(const std::string& key) const;

	std::string getHttpVersion() const;

	std::string getQueryParameter(const std::string& key) const;

	std::string getCookie(const std::string& key) const;

	std::string getMethod() const;

	std::string getUrl() const;

	std::string getBody() const;

	/**
	* @brief Parses the request string
	* @param reqString The request string
	*/
	void parseRequest(const std::string& reqString);
};

