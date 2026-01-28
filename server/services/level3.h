#ifndef LEVEL3_H
#define LEVEL3_H

#include <memory>
#include <string>

#include "../models/account1.h"
#include "level2.h"

class Level3Service : public Level2Service {
 private:
  std::unique_ptr<Account1> secretAccount = std::make_unique<Account1>(
      "secret", "user3", "znFcptZaqyGeN6g61K9T1InXtwpUD1", "verylongsecret");
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user3", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user3", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user3", "pass3", "secret3")};

 public:
  Level3Service() = default;
  ~Level3Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;
};

#endif