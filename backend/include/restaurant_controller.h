#ifndef RESTAURANT_CONTROLLER_H
#define RESTAURANT_CONTROLLER_H

#include <string>
#include <vector>
#include <tuple>

void add_restaurant(const std::string& name, const std::string& address);
std::vector<std::tuple<int, std::string, std::string>> get_restaurants();

#endif // RESTAURANT_CONTROLLER_H
