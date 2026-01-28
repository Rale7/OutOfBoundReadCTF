
#include "../services/level1.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "../models/account1.h"

std::string Level1Service::getAccounts() {
  std::string result = "[";
  for (int i = 0; i <= 3; ++i) {
    result += accounts[i]->serialize();
    if (i < 3) {
      result += ",";
    }
  }
  result += "]";
  return result;
}

std::string Level1Service::getAccount(int index) {
  if (index >= sizeof(accounts) / sizeof(accounts[0]) && index > 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level1Service::changeAccount(const Account1& newAccount) {
  for (uint32_t index = 0; index < sizeof(accounts) / sizeof(accounts[0]);
       ++index) {
    if (std::string(accounts[index]->service) ==
        std::string(newAccount.service)) {
      accounts[index] =
          std::make_unique<Account1>(newAccount.service, newAccount.username,
                                     newAccount.password, newAccount.secret);
      break;
    }
  }
}

std::string Level1Service::exportFromFile(size_t size) {
  return "{\"export\":\"data export not implemented.\"}";
}

void Level1Service::importToFile(const char data[], size_t size) {
  // Base implementation - do nothing
  (void)data;  // Suppress unused parameter warning
  (void)size;  // Suppress unused parameter warning
}
