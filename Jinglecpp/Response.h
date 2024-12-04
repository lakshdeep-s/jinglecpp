/**
 * @file Response.h
 * @brief Response class for handling HTTP responses
 * @author Lakshdeep Singh \link https://www.github.com/lakshdeep-s
 */
#include "pch.h"
#pragma once
#include "nlohmann/json.hpp"

 /**
  * @class Response
  * @brief Response class for handling HTTP responses
  */
class Response
{
private:
    /**
     * @var version
     * @brief The HTTP version used in the response (default: "1.1").
     */
    std::string version;

    /**
     * @var statusCode
     * @brief The HTTP status code for the response (e.g., 200, 404).
     */
    unsigned short statusCode;

    /**
     * @var statusText
     * @brief The status text corresponding to the status code (e.g., "OK", "Not Found").
     */
    std::string statusText;

    /**
     * @var body
     * @brief The body content of the HTTP response.
     */
    std::string body;

    /**
     * @var headers
     * @brief A map of custom headers for the HTTP response.
     */
    std::map<std::string, std::string> headers;

    /**
     * @var statusCodes
     * @brief A map of standard HTTP status codes and their corresponding status texts.
     */
    std::map<unsigned short, std::string> statusCodes = {
        {200,"OK"},
        {201,"Created"},
        {400,"Bad Request"},
        {403,"Unauthorized"},
        {404,"Not Found"},
        {500,"Internal Server Error"}
    };

public:
/**
* @brief Constructor for Response class
* @param version HTTP version (default: "1.1")
*/
    Response(const std::string& version = "1.1");

    /**
     * @brief Destructor for Response class
     */
    ~Response() {};

    /**
     * @brief Sets the HTTP status code and status text
     * @param statusCode HTTP status code
     * @return Reference to the Response object
     */
    Response& status(unsigned short statusCode);

    /**
     * @brief Sets a custom header
     * @param key Header key
     * @param value Header value
     * @return Reference to the Response object
     */
    Response& setHeader(const std::string& key, const std::string& value);

    /**
     * @brief Sets multiple custom headers
     * @param customHeaders Map of custom headers
     * @return Reference to the Response object
     */
    Response& setHeaders(const std::map<std::string&, std::string>& customHeaders);

    /**
     * @brief Gets all headers
     * @return Map of headers
     */
    std::map<std::string, std::string> getHeaders() const;

    /**
     * @brief Sends a response with the given data and content type
     * @param data Response data
     * @param contentType Content type of the response
     * @return Reference to the Response object
     */
    Response& send(const std::string& data, const std::string& contentType = "text/plain");

    /**
     * @brief Sends a file as response
     * @param filePath Path to the file
     * @return Reference to the Response object
     */
    Response& sendFile(const std::string& filePath);

    /**
     * @brief Sends a JSON response
     * @param jsonObject JSON object to be sent
     * @return Reference to the Response object
     */
    Response& json(nlohmann::json& jsonObject);

    /**
     * @brief Gets the response as a string
     * @return Response string
     */
    const std::string getResponse() const;

    /**
     * @brief Gets the current date
     * @return Current date string
     */
    std::string getCurrentDate() const;
};
