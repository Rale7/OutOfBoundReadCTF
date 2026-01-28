
#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#include "../utils/http_request.h"

struct Route {
  std::string path;
  HttpRequestMethod method;

  Route(const std::string& p, HttpRequestMethod m) : path(p), method(m) {}

  bool operator==(const Route& other) const {
    return path == other.path && method == other.method;
  }
};

struct RouteHash {
  std::size_t operator()(const Route& route) const {
    return std::hash<std::string>()(route.path) ^
           (std::hash<int>()(static_cast<int>(route.method)) << 1);
  }
};

#endif