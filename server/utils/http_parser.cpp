#include "http_parser.h"

#include <algorithm>
#include <cctype>
#include <sstream>

HttpRequest HttpParser::parse(const std::string& raw_request) {
  HttpRequest request;
  request.method = HttpRequestMethod::UNKNOWN;
  request.version = HttpVersion::UNKNOWN_VERSION;

  if (raw_request.empty()) {
    throw HttpParseException("Empty request");
  }

  std::istringstream stream(raw_request);
  std::string line;

  // Parse request line (metod, putanja, verzija)
  if (std::getline(stream, line)) {
    parseRequestLine(line, request);
  } else {
    throw HttpParseException("Missing request line");
  }

  // Validate that we parsed a valid method and version
  if (request.method == HttpRequestMethod::UNKNOWN) {
    throw HttpParseException("Invalid HTTP method");
  }
  if (request.version == HttpVersion::UNKNOWN_VERSION) {
    throw HttpParseException("Invalid HTTP version");
  }

  // Parse headers
  while (std::getline(stream, line)) {
    if (line == "\r" || line.empty()) {
      break;
    }
    parseHeader(line, request);
  }

  // Parse body
  std::string body_line;
  while (std::getline(stream, body_line)) {
    if (!request.body.empty()) {
      request.body += "\n";
    }
    request.body += body_line;
  }

  return request;
}

void HttpParser::parseRequestLine(const std::string& line,
                                  HttpRequest& request) {
  std::istringstream iss(line);
  std::string method_str, path, version_str;

  iss >> method_str >> path >> version_str;

  // Check if we got all required parts
  if (method_str.empty() || path.empty() || version_str.empty()) {
    throw HttpParseException("Malformed request line");
  }

  // Parsiranje metode
  method_str = toUpperCase(method_str);
  if (method_str == "GET") {
    request.method = HttpRequestMethod::GET;
  } else if (method_str == "POST") {
    request.method = HttpRequestMethod::POST;
  } else if (method_str == "PUT") {
    request.method = HttpRequestMethod::PUT;
  } else if (method_str == "DELETE") {
    request.method = HttpRequestMethod::DELETE;
  } else if (method_str == "OPTIONS") {
    request.method = HttpRequestMethod::OPTIONS;
  } else {
    request.method = HttpRequestMethod::UNKNOWN;
  }

  // Parsiranje putanje
  request.path = path;

  // Parsiranje verzije
  if (version_str.find("1.0") != std::string::npos) {
    request.version = HttpVersion::HTTP_1_0;
  } else if (version_str.find("1.1") != std::string::npos) {
    request.version = HttpVersion::HTTP_1_1;
  } else if (version_str.find("2.0") != std::string::npos) {
    request.version = HttpVersion::HTTP_2_0;
  } else {
    request.version = HttpVersion::UNKNOWN_VERSION;
  }
}

void HttpParser::parseHeader(const std::string& line, HttpRequest& request) {
  size_t colon_pos = line.find(':');
  if (colon_pos != std::string::npos) {
    std::string key = line.substr(0, colon_pos);
    std::string value = line.substr(colon_pos + 1);

    // Uklanjanje vodećih/pratećih razmaka
    trim(key);
    trim(value);

    request.headers[key] = value;
  }
}

std::string HttpParser::toUpperCase(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return result;
}

void HttpParser::trim(std::string& str) {
  // Uklonjavanje vodećih razmaka
  size_t start = str.find_first_not_of(" \t\r\n");
  if (start != std::string::npos) {
    str = str.substr(start);
  }

  // Uklonjavanje pratećih razmaka
  size_t end = str.find_last_not_of(" \t\r\n");
  if (end != std::string::npos) {
    str = str.substr(0, end + 1);
  }
}