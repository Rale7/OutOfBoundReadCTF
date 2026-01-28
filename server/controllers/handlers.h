#ifndef HANDLERS_H
#define HANDLERS_H

#include <string>

#include "../utils/http_request.h"

class Handlers {
 public:
  static std::string handleHome(const HttpRequest& request);
  static std::string handleAbout(const HttpRequest& request);
  static std::string handleApi(const HttpRequest& request);
  static std::string getAccounts(const HttpRequest& request);
  static std::string login(const HttpRequest& request);
  static std::string getSingleAccount(const HttpRequest& request);
  static std::string changeAccount(const HttpRequest& request);
  static std::string exportFromFile(const HttpRequest& request);
  static std::string importToFile(const HttpRequest& request);
  static std::string handleOptions(const HttpRequest& request);
  static std::string handleBadRequest(const std::string& message);
};

#endif
