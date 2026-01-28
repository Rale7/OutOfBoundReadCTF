#ifndef LEVEL10_H
#define LEVEL10_H

#include <memory>
#include <string>

#include "../models/account1.h"
#include "level1.h"

class Level10Service : public Level1Service {
 private:
  std::unique_ptr<Account1> accounts[1]{std::make_unique<Account1>(
      "instagram", "you can't do this in browser", "pass1", "secret1")};

 public:
  Level10Service() = default;
  virtual ~Level10Service() = default;
  virtual std::string getAccount(int index);

  virtual std::string getAccounts();

  virtual void changeAccount(const Account1& newAccount);
};

#endif