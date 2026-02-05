#include "auth_parser.h"

#include <algorithm>
#include <iostream>

namespace {
const std::string BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int charToValue(char c) {
  size_t pos = BASE64_CHARS.find(c);
  if (pos == std::string::npos) return -1;
  return pos;
}

std::string decodeBase64Internal(const std::string& encoded) {
  std::string decoded;
  int val = 0;
  int bits = -8;

  for (unsigned char c : encoded) {
    if (c == '=') break;

    int digit = charToValue(c);
    if (digit < 0) continue;

    val = (val << 6) + digit;
    bits += 6;

    while (bits >= 0) {
      decoded.push_back(static_cast<char>((val >> bits) & 0xFF));
      bits -= 8;
    }
  }
  return decoded;
}
}  // namespace

AuthCredentials AuthParser::parseBasicAuth(const HttpRequest& request) {
  AuthCredentials creds{"", "", false};

  auto it = request.headers.find("Authorization");
  if (it == request.headers.end()) {
    return creds;  // No auth header
  }

  std::string auth_header = it->second;

  if (auth_header.substr(0, 6) != "Basic ") {
    return creds;
  }

  std::string encoded = auth_header.substr(6);
  std::string decoded = decodeBase64(encoded);
  size_t colon_pos = decoded.find(':');
  if (colon_pos == std::string::npos) {
    return creds;
  }

  creds.username = decoded.substr(0, colon_pos);
  creds.password = decoded.substr(colon_pos + 1);
  creds.valid = true;

  return creds;
}

std::string AuthParser::decodeBase64(const std::string& encoded) {
  return decodeBase64Internal(encoded);
}
