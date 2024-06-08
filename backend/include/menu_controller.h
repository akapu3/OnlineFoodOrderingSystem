#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <string>
#include <vector>
#include <tuple>

void add_menu_item(int restaurant_id, const std::string& name, const std::string& description, double price);
std::vector<std::tuple<int, std::string, std::string, double>> get_menu_items(int restaurant_id);

#endif // MENU_CONTROLLER_H
