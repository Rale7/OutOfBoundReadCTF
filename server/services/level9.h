#ifndef LEVEL9_H
#define LEVEL9_H

#include <memory>
#include <string>

#include "../models/account1.h"
#include "level1.h"

class Level9Service : public Level1Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user9", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user9", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user9", "pass3", "secret3")};

 public:
  Level9Service() = default;
  virtual ~Level9Service() = default;

  virtual std::string getAccount(int index);

  virtual std::string getAccounts();

  virtual void changeAccount(const Account1& newAccount);

  virtual std::string exportFromFile(size_t size);

  virtual void importToFile(const char data[], size_t size);
};

#endif