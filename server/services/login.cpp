
#include "login.h"

#include <set>

namespace login {

static std::set<std::pair<std::string, std::string>> usersDatabase() {
  std::set<std::pair<std::string, std::string>> db;
  db.insert(std::make_pair("user1", "password1"));
  db.insert(std::make_pair("user2", "mF9W63nCxB7arsEPMBP4p4WzVt1ip7"));
  db.insert(std::make_pair("user3", "L3sO6jaVCf86dZX2YGFYEF5qz90MK5"));
  db.insert(std::make_pair("user4", "znFcptZaqyGeN6g61K9T1InXtwpUD1"));
  db.insert(std::make_pair("user5", "6DMut59M86Zy2l30WfSBGjEvqgEdq8"));
  db.insert(std::make_pair("user6", "Zb1qlh35FjX2hpDx6CitV4AogjxHmT"));
  db.insert(std::make_pair("user7", "49VeKM4jE9kQS9ZgeZnRFBkTJsR84c"));
  db.insert(std::make_pair("user8", "7KOSy5uLVbd1V5zXIHZSj2ianyWLw5"));
  db.insert(std::make_pair("user9", "MbD8HJDPzHS1V6iasFet61KY7ooKAh"));
  db.insert(std::make_pair("user10", "4H91sgkzIoF66ftI6p3vrhED9sbRN9"));
  return db;
}

int login_service(const std::string& username, const std::string& password) {
  static const auto db = usersDatabase();

  if (db.find(std::make_pair(username, password)) != db.end()) {
    return 1;  // Uspešna prijava
  } else {
    return 0;  // Neuspešna prijava
  }
}
}  // namespace login