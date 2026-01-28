#include <memory>
#include <string>

#include "level3.h"

class Level4Service : public Level3Service {
 private:
  std::unique_ptr<Account1> accounts[3]{
      std::make_unique<Account1>("instagram", "user4", "pass1", "secret1"),
      std::make_unique<Account1>("facebook", "user4", "pass2", "secret2"),
      std::make_unique<Account1>("tiktok", "user4", "pass3", "secret3")};

 public:
  Level4Service() = default;
  ~Level4Service() = default;

  virtual std::string getAccounts() override;

  virtual std::string getAccount(int index) override;

  virtual void changeAccount(const Account1& newAccount) override;
};