#ifndef ACCOUNT3_H
#define ACCOUNT3_H

#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>

#include "../utils/serializable.h"

#define POOL_SIZE 128

struct Account3 : public Serializable {
  char service[32];
  char username[32];
  char password[32];
  char secret[32];

  Account3(const char* svc, const char* user, const char* pass,
           const char* sec);
  Account3(const char* svc, const char* user, const char* pass);
  Account3() = default;

  std::string serialize() const override;
  void deserialize(const std::string& data) override;

  static void* operator new(std::size_t sz);
  static void operator delete(void* p) noexcept;

 private:
  static bool s_used[POOL_SIZE];
};

#endif
