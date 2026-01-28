#include "level4.h"

#include <cstdint>
#include <iostream>

std::string Level4Service::getAccounts() {
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

std::string Level4Service::getAccount(int index) {
  if (index >= 3 || index < 0) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}

void Level4Service::changeAccount(const Account1& newAccount) {
  for (uint32_t index = 0; index < sizeof(accounts) / sizeof(accounts[0]);
       ++index) {
    if (std::string(accounts[index]->service) ==
        std::string(newAccount.service)) {
      accounts[index] = std::make_unique<Account1>(
          newAccount.service, newAccount.username, newAccount.password,
          "6DMut59M86Zy2l30WfSBGjEvqgEdq8");
      break;
    }
  }
  for (auto& acc : accounts) {
    std::cout << acc->serialize() << std::endl;
  }
}