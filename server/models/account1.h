#ifndef ACCOUNT1_H
#define ACCOUNT1_H

#include "../utils/serializable.h"

struct Account1 : public Serializable {
  char service[32];
  char username[32];
  char password[32];
  char secret[32];

  Account1(const char* svc, const char* user, const char* pass,
           const char* sec);

  Account1() = default;

  std::string serialize() const override;
  void deserialize(const std::string& data) override;
};

#endif