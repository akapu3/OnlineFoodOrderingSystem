#ifndef ORDER_CONTROLLER_H
#define ORDER_CONTROLLER_H

#include <string>
#include <vector>
#include <tuple>

void place_order(int user_id, int restaurant_id, const std::vector<std::tuple<int, int>>& items);
std::vector<std::tuple<int, int, int, double, std::string, std::string>> get_orders(int user_id);

#endif // ORDER_CONTROLLER_H
