#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <string>

void register_user(const std::string& username, const std::string& password, const std::string& email);
bool login_user(const std::string& username, const std::string& password);

#endif // USER_CONTROLLER_H
