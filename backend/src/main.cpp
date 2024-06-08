#include "crow_all.h"
#include "db_connection.h"
#include "user_controller.h"
#include "restaurant_controller.h"
#include "menu_controller.h"
#include "order_controller.h"

int main() {
    connect_db();

    crow::SimpleApp app;

    // User Registration
    CROW_ROUTE(app, "/register").methods(crow::HTTPMethod::POST)
            ([](const crow::request& req) {
                auto x = crow::json::load(req.body);
                if (!x) return crow::response(400);

                std::string username = x["username"].s();
                std::string password = x["password"].s();
                std::string email = x["email"].s();

                register_user(username, password, email);
                return crow::response(200);
            });

    // User Login
    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)
            ([](const crow::request& req) {
                auto x = crow::json::load(req.body);
                if (!x) return crow::response(400);

                std::string username = x["username"].s();
                std::string password = x["password"].s();

                if (login_user(username, password)) {
                    return crow::response(200);
                } else {
                    return crow::response(401);
                }
            });

    // Get Restaurants
    CROW_ROUTE(app, "/restaurants").methods(crow::HTTPMethod::GET)
            ([]() {
                auto restaurants = get_restaurants();
                crow::json::wvalue x;
                for (const auto& restaurant : restaurants) {
                    x["restaurants"].push_back(crow::json::wvalue{
                            {"id", std::get<0>(restaurant)},
                            {"name", std::get<1>(restaurant)},
                            {"address", std::get<2>(restaurant)}
                    });
                }
                return crow::response(x);
            });

    // Get Menu for a Restaurant
    CROW_ROUTE(app, "/menu/<int>").methods(crow::HTTPMethod::GET)
            ([](int restaurant_id) {
                auto menu_items = get_menu_items(restaurant_id);
                crow::json::wvalue x;
                for (const auto& item : menu_items) {
                    x["menu_items"].push_back(crow::json::wvalue{
                            {"id", std::get<0>(item)},
                            {"name", std::get<1>(item)},
                            {"description", std::get<2>(item)},
                            {"price", std::get<3>(item)}
                    });
                }
                return crow::response(x);
            });

    // Place an Order
    CROW_ROUTE(app, "/order").methods(crow::HTTPMethod::POST)
            ([](const crow::request& req) {
                auto x = crow::json::load(req.body);
                if (!x) return crow::response(400);

                int user_id = x["user_id"].i();
                int restaurant_id = x["restaurant_id"].i();
                std::vector<std::tuple<int, int>> items;
                for (const auto& item : x["items"]) {
                    items.emplace_back(item["menu_item_id"].i(), item["quantity"].i());
                }

                place_order(user_id, restaurant_id, items);
                return crow::response(200);
            });

    app.port(8080).multithreaded().run();
    return 0;
}
