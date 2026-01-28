#ifndef AUTH_PARSER_H
#define AUTH_PARSER_H

#include <string>
#include <unordered_map>

#include "../utils/http_request.h"

struct AuthCredentials {
  std::string username;
  std::string password;
  bool valid;
};

class AuthParser {
 public:
  // Parse Basic Auth from request headers
  static AuthCredentials parseBasicAuth(const HttpRequest& request);

 private:
  // Decode Base64 string
  static std::string decodeBase64(const std::string& encoded);
};

#endif
