#ifndef SERVICES_LEVEL6_H
#define SERVICES_LEVEL6_H

#include <memory>
#include <string>

#include "../models/account3.h"
#include "level1.h"

class Level6Service : public Level1Service {
 private:
  std::unique_ptr<Account3> accounts[3]{
      std::make_unique<Account3>("instagram", "user6", "pass1", "secret1"),
      std::make_unique<Account3>("facebook", "user6", "pass2", "secret2"),
      std::make_unique<Account3>("tiktok", "user6", "pass3", "secret3")};

 public:
  Level6Service() = default;
  ~Level6Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;

  virtual void changeAccount(const Account1& newAccount) override;
};

#endif