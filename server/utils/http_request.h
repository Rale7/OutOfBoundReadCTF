#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <unordered_map>

enum HttpRequestMethod { GET, POST, PUT, DELETE, OPTIONS, UNKNOWN };

enum HttpVersion { HTTP_1_0, HTTP_1_1, HTTP_2_0, UNKNOWN_VERSION };

struct HttpRequest {
  HttpRequestMethod method;
  std::string path;
  HttpVersion version;
  std::unordered_map<std::string, std::string> headers;
  std::string body;
  // Path parameters extracted by the router (e.g., from "/users/:id")
  std::unordered_map<std::string, std::string> params;
};

#endif