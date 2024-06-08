#include "restaurant_controller.h"
#include "db_connection.h"

void add_restaurant(const std::string& name, const std::string& address) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO restaurants (name, address) VALUES (?, ?)"));
    pstmt->setString(1, name);
    pstmt->setString(2, address);
    pstmt->execute();
}

std::vector<std::tuple<int, std::string, std::string>> get_restaurants() {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM restaurants"));
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    std::vector<std::tuple<int, std::string, std::string>> restaurants;

    while (res->next()) {
        restaurants.emplace_back(res->getInt("id"), res->getString("name"), res->getString("address"));
    }
    return restaurants;
}
