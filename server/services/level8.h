#ifndef LEVEL8_H
#define LEVEL8_H

#include <memory>
#include <string>

#include "../models/account1.h"
#include "level1.h"

class Level8Service : public Level1Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user8", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user8", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user8", "pass3", "secret3")};

  char buffer[256];
  char guard[4096] = "MbD8HJDPzHS1V6iasFet61KY7ooKAh";

 public:
  Level8Service() = default;
  virtual ~Level8Service() = default;

  virtual std::string getAccount(int index);

  virtual std::string getAccounts();

  virtual void changeAccount(const Account1& newAccount);

  virtual std::string exportFromFile(size_t size);

  virtual void importToFile(const char data[], size_t size);
};

#endif