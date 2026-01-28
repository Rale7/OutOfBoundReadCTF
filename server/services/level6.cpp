#include "level6.h"

#include <iostream>

std::string Level6Service::getAccounts() {
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

std::string Level6Service::getAccount(int index) {
  if (index >= 3 || index < 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level6Service::changeAccount(const Account1& newAccount) {
  for (int i = 0; i < 3; ++i) {
    if (std::string(accounts[i]->service) == std::string(newAccount.service)) {
      accounts[i] = nullptr;
      accounts[i] = std::make_unique<Account3>(
          newAccount.service, newAccount.username, newAccount.password);
      break;
    }
  }
}