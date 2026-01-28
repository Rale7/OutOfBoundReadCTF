#ifndef LEVEL1_H
#define LEVEL1_H

#include <memory>
#include <string>

#include "../models/account1.h"

class Level1Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user1", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user1", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user1", "pass3", "secret3")};
  std::unique_ptr<Account1> secretAccount = std::make_unique<Account1>(
      "secret", "user1", "mF9W63nCxB7arsEPMBP4p4WzVt1ip7", "verylongsecret");

 public:
  Level1Service() = default;
  virtual ~Level1Service() = default;

  virtual std::string getAccount(int index);

  virtual std::string getAccounts();

  virtual void changeAccount(const Account1& newAccount);

  virtual std::string exportFromFile(size_t size);

  virtual void importToFile(const char data[], size_t size);
};

#endif
