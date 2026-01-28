#ifndef LEVEL7_SERVICE_H
#define LEVEL7_SERVICE_H

#include <memory>
#include <string>

#include "level1.h"

class Level7Service : public Level1Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user7", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user7", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user7", "pass3", "secret3")};

 public:
  Level7Service() = default;
  ~Level7Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;

  virtual void changeAccount(const Account1& newAccount) override;

  virtual std::string exportFromFile(size_t size) override;
};

#endif