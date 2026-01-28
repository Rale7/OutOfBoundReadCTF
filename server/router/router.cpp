#include "router.h"

#include <cstdio>
#include <regex>

#include "../utils/safe_executor.h"

namespace {
// Convert pattern like "/users/:id/posts/:postId" into regex and param names.
// Result regex: ^/users/([^/]+)/posts/([^/]+)$ with params ["id", "postId"].
std::pair<std::regex, std::vector<std::string>> compilePattern(
    const std::string& pattern) {
  std::string rx = "^";
  std::vector<std::string> params;

  for (size_t i = 0; i < pattern.size();) {
    char c = pattern[i];
    if (c == ':') {
      // read param name
      size_t j = i + 1;
      while (j < pattern.size() && pattern[j] != '/') {
        j++;
      }
      std::string name = pattern.substr(i + 1, j - (i + 1));
      params.push_back(name);
      rx += "([^/]+)";  // capture one path segment
      i = j;
      continue;
    }
    // Escape regex special chars for literal path parts
    switch (c) {
      case '.':
      case '+':
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
      case '^':
      case '$':
      case '|':
      case '?':
      case '*':
        rx += '\\';
        rx += c;
        break;
      default:
        rx += c;
        break;
    }
    i++;
  }

  rx += "$";
  return {std::regex(rx), params};
}
}  // namespace

void Router::addRoute(const std::string& pattern, HttpRequestMethod method,
                      RouteHandler handler) {
  auto [rx, params] = compilePattern(pattern);
  RouteEntry entry{pattern, rx, params, method, handler};
  routes.push_back(std::move(entry));
}

std::string Router::handleRequest(const HttpRequest& request) {
  for (const auto& entry : routes) {
    if (entry.method != request.method) continue;
    std::smatch m;
    if (std::regex_match(request.path, m, entry.regex)) {
      HttpRequest req = request;  // make a copy to attach params
      req.params.clear();
      // m[0] is the whole match; captures start at 1
      for (size_t i = 0; i < entry.params.size() && (i + 1) < m.size(); ++i) {
        req.params[entry.params[i]] = m[i + 1].str();
      }

      // Execute the handler safely to catch crashes
      return SafeExecutor::executeHandler(
          [&entry, &req]() { return entry.handler(req); });
    }
  }

  // Ako nema pronađene rute
  return generateNotFoundResponse();
}

std::string Router::generateNotFoundResponse() const {
  return "HTTP/1.1 404 Not Found\r\n"
         "Content-Type: text/plain\r\n"
         "Content-Length: 9\r\n"
         "\r\n"
         "Not Found";
}
