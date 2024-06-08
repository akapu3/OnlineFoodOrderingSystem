#include "menu_controller.h"
#include "db_connection.h"

void add_menu_item(int restaurant_id, const std::string& name, const std::string& description, double price) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO menu_items (restaurant_id, name, description, price) VALUES (?, ?, ?, ?)"));
    pstmt->setInt(1, restaurant_id);
    pstmt->setString(2, name);
    pstmt->setString(3, description);
    pstmt->setDouble(4, price);
    pstmt->execute();
}

std::vector<std::tuple<int, std::string, std::string, double>> get_menu_items(int restaurant_id) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM menu_items WHERE restaurant_id=?"));
    pstmt->setInt(1, restaurant_id);
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    std::vector<std::tuple<int, std::string, std::string, double>> menu_items;

    while (res->next()) {
        menu_items.emplace_back(res->getInt("id"), res->getString("name"), res->getString("description"), res->getDouble("price"));
    }
    return menu_items;
}

