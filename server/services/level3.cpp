#include "level3.h"

#include <iostream>

std::string Level3Service::getAccounts() {
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

std::string Level3Service::getAccount(int index) {
  if (index >= 3) {
    return "[]";
  }
  return "[" + accounts[index]->serialize() + "]";
}