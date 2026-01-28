#include "level7.h"

#include <cstring>
#include <iostream>

std::string Level7Service::getAccounts() {
  std::string result = "[";
  for (int i = 0; i < 3; ++i) {
    result += accounts[i]->serialize();
    if (i < 2) {
      result += ",";
    }
  }
  result += "]";
  return result;
}

std::string Level7Service::getAccount(int index) {
  if (index >= 3 || index < 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level7Service::changeAccount(const Account1& newAccount) {
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

std::string Level7Service::exportFromFile(size_t size) {
  char guard[4096] = {0};
  char buffer[256] = {0};

  FILE* file = fopen("level7_export.json", "r");
  if (!file) {
    return "{\"export\":\"error opening file.\"}";
  }
  fread(buffer, 1, size, file);

  fclose(file);

  return std::string("{\"export\":\"") + std::string(buffer) + "\"}";
}