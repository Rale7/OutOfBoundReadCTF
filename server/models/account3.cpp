#include "account3.h"

#include <cstring>
#include <iostream>

static typename std::aligned_storage<sizeof(Account3), alignof(Account3)>::type
    s_pool[POOL_SIZE];
// Static storage definitions

bool Account3::s_used[POOL_SIZE] = {false};

Account3::Account3(const char* svc, const char* user, const char* pass,
                   const char* sec) {
  std::strcpy(service, svc);
  std::strcpy(username, user);
  std::strcpy(password, pass);
  std::strcpy(secret, sec);
}

Account3::Account3(const char* svc, const char* user, const char* pass) {
  std::strcpy(service, svc);
  std::strcpy(username, user);
  std::strcpy(password, pass);
}

std::string Account3::serialize() const {
  std::string json = "{";
  json += "\"service\":\"";
  json.append(service);
  json += "\",";
  json += "\"username\":\"";
  json.append(username);
  json += "\",";
  json += "\"password\":\"";
  json.append(password);
  json += "\",";
  json += "\"secret\":\"";
  json.append(secret);
  json += "\"";
  json += "}";
  return json;
}

void Account3::deserialize(const std::string& data) {
  std::string s = extractJsonStringValue(data, "service");
  std::string u = extractJsonStringValue(data, "username");
  std::string p = extractJsonStringValue(data, "password");

  std::strcpy(service, s.c_str());
  std::strcpy(username, u.c_str());
  std::strcpy(password, p.c_str());
}

void* Account3::operator new(std::size_t sz) {
  // Try pool first
  if (sz == sizeof(Account3)) {
    for (std::size_t i = 0; i < POOL_SIZE; ++i) {
      if (!s_used[i]) {
        s_used[i] = true;
        return &s_pool[i];
      }
    }
  }
  // Fallback to global operator new
  return ::operator new(sz);
}

void Account3::operator delete(void* p) noexcept {
  Account3* accountPtr = static_cast<Account3*>(p);
  strcpy(accountPtr->secret, "49VeKM4jE9kQS9ZgeZnRFBkTJsR84c");

  if (!p) return;
  // Check if pointer belongs to our pool
  auto base = reinterpret_cast<std::uintptr_t>(&s_pool[0]);
  auto end = reinterpret_cast<std::uintptr_t>(&s_pool[POOL_SIZE]);
  auto addr = reinterpret_cast<std::uintptr_t>(p);

  if (addr >= base && addr < end) {
    // Compute index
    std::size_t index = (addr - base) / sizeof(Account3);
    if (index < POOL_SIZE) {
      s_used[index] = false;
      return;
    }
  }
  // Fallback to global delete
  ::operator delete(p);
}
