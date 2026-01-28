#ifndef SERVICES_LEVEL2_H
#define SERVICES_LEVEL2_H

#include <memory>
#include <string>

#include "../models/account1.h"
#include "level1.h"

class Level2Service : public Level1Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user2", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user2", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user2", "pass3", "secret3")};
  std::unique_ptr<Account1> secretAccount = std::make_unique<Account1>(
      "secret", "user3", "L3sO6jaVCf86dZX2YGFYEF5qz90MK5", "verylongsecret");

 public:
  Level2Service() = default;
  ~Level2Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;
};

#endif