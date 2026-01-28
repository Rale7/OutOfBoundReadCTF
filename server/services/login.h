#ifndef SERVICES_LOGIN_H
#define SERVICES_LOGIN_H

#include <string>
namespace login {
int login_service(const std::string& username, const std::string& password);
}
#endif  // SERVICES_LOGIN_H