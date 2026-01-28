#ifndef ACCOUNT2_H
#define ACCOUNT2_H

#include "../utils/serializable.h"

struct Account2 : public Serializable {
  char* service = nullptr;
  char* username = nullptr;
  char* password = nullptr;
  char* secret = nullptr;

  Account2(const char* svc, const char* user, const char* pass,
           const char* sec);
  Account2() = default;

  std::string serialize() const override;
  void deserialize(const std::string& data) override;

 private:
  void copyFields(const char* svc, const char* user, const char* pass,
                  const char* sec);
};

#endif