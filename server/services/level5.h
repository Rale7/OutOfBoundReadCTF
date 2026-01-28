#include <memory>
#include <string>

#include "../models/account2.h"
#include "level1.h"

class Level5Service : public Level1Service {
 private:
  std::unique_ptr<Account2> accounts[3]{
      std::make_unique<Account2>("instagram", "user5", "pass1", "secret1"),
      std::make_unique<Account2>("facebook", "user5", "pass2", "secret2"),
      std::make_unique<Account2>("tiktok", "user5", "pass3", "secret3")};

 public:
  Level5Service() = default;
  ~Level5Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;

  virtual void changeAccount(const Account1& newAccount) override;
};