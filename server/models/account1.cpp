#include "account1.h"

#include <cstring>
#include <string>

Account1::Account1(const char* svc, const char* user, const char* pass,
                   const char* sec) {
  std::strcpy(service, svc);
  std::strcpy(username, user);
  std::strcpy(password, pass);
  std::strcpy(secret, sec);
}

std::string Account1::serialize() const {
  // Naivna serijalizacija u JSON bez escaping-a
  std::string json = "{";
  json += "\"service\":\"";
  json.append(service);
  json += "\",";
  json += "\"username\":\"";
  json.append(username);
  json += "\",";
  json += "\"password\":\"";
  json.append(password);
  json += "\"";
  json += "}";
  return json;
}

void Account1::deserialize(const std::string& data) {
  // Naivna deserializacija (bez validacije JSON-a i escaping-a)
  std::string s = extractJsonStringValue(data, "service");
  std::string u = extractJsonStringValue(data, "username");
  std::string p = extractJsonStringValue(data, "password");

  std::strcpy(service, s.c_str());

  std::strcpy(username, u.c_str());

  std::strcpy(password, p.c_str());

  std::strcpy(secret, "");
}
