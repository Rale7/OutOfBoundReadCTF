
#include "level2.h"

std::string Level2Service::getAccounts() {
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

std::string Level2Service::getAccount(int index) {
  return "[" + accounts[index]->serialize() + "]";
}