#include "level5.h"

#include <iostream>

std::string Level5Service::getAccounts() {
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

std::string Level5Service::getAccount(int index) {
  if (index >= 3 || index < 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level5Service::changeAccount(const Account1& newAccount) {
  for (uint32_t index = 0; index < sizeof(accounts) / sizeof(accounts[0]);
       ++index) {
    if (std::string(accounts[index]->service,
                    accounts[index]->username - accounts[index]->service) ==
        std::string(newAccount.service)) {
      accounts[index] = std::make_unique<Account2>(
          newAccount.service, newAccount.username, newAccount.password,
          "Zb1qlh35FjX2hpDx6CitV4AogjxHmT");
      break;
    }
  }
}