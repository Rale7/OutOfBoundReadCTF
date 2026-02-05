#include "account2.h"

#include <cstdint>
#include <cstring>

Account2::Account2(const char* svc, const char* user, const char* pass,
                   const char* sec) {
  copyFields(svc, user, pass, sec);
}

std::string Account2::serialize() const {
  std::string json = "{";
  json += "\"service\":\"";
  if (username - service > 0) {
    json.append(std::string(service, username - service));
  } else {
    json.append(service);
  }
  json += "\",";
  json += "\"username\":\"";
  if (secret - password > 0) {
    json.append(std::string(username, secret - password));
  } else {
    json.append(username);
  }
  json += "\",";
  json += "\"password\":\"";
  if (secret - password > 0) {
    json.append(std::string(password, secret - password));
  } else {
    json.append(password);
  }
  json += "\"";
  json += "}";
  return json;
}

void Account2::deserialize(const std::string& data) {
  std::string s = extractJsonStringValue(data, "service");
  std::string u = extractJsonStringValue(data, "username");
  std::string p = extractJsonStringValue(data, "password");

  copyFields(s.c_str(), u.c_str(), p.c_str(), "");
}

void Account2::copyFields(const char* svc, const char* user, const char* pass,
                          const char* sec) {
  if (service) {
    free(service);
  }

  size_t svc_len = std::strlen(svc);
  size_t user_len = std::strlen(user);
  size_t pass_len = std::strlen(pass);
  size_t sec_len = std::strlen(sec);

  size_t account_len = svc_len + user_len + pass_len + sec_len;
  service = static_cast<char*>(std::malloc(account_len + 1));

  strcpy(service, svc);
  username = service + svc_len;
  strcpy(username, user);
  password = username + user_len;
  strcpy(password, pass);
  secret = password + pass_len;
  strcpy(secret, sec);
  service[account_len] = '\0';
}