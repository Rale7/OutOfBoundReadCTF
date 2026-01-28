#include "level10.h"

#include <cstring>
#include <iostream>

std::string Level10Service::getAccounts() {
  std::string result = "[";
  for (int i = 0; i < 1; ++i) {
    result += accounts[i]->serialize();
    if (i < 0) {
      result += ",";
    }
  }
  result += "]";
  return result;
}

std::string Level10Service::getAccount(int index) {
  if (index >= 1 || index < 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level10Service::changeAccount(const Account1& newAccount) {
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