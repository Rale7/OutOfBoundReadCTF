#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <stdexcept>
#include <string>

#include "http_request.h"

class HttpParseException : public std::runtime_error {
 public:
  explicit HttpParseException(const std::string& message)
      : std::runtime_error("Could not parse request: " + message) {}
};

class HttpParser {
 public:
  static HttpRequest parse(const std::string& raw_request);

 private:
  static void parseRequestLine(const std::string& line, HttpRequest& request);

  static void parseHeader(const std::string& line, HttpRequest& request);

  static std::string toUpperCase(const std::string& str);

  static void trim(std::string& str);
};

#endif
