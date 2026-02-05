#ifndef ROUTER_H
#define ROUTER_H

#include <functional>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "../utils/http_request.h"

using RouteHandler = std::function<std::string(const HttpRequest&)>;

class Router {
 private:
  struct RouteEntry {
    std::string pattern;
    std::regex regex;
    std::vector<std::string> params;
    HttpRequestMethod method;
    RouteHandler handler;
  };

  std::vector<RouteEntry> routes;

 public:
  void addRoute(const std::string& pattern, HttpRequestMethod method,
                RouteHandler handler);

  std::string handleRequest(const HttpRequest& request);

 private:
  std::string generateNotFoundResponse() const;
};

#endif
