#include "order_controller.h"
#include "db_connection.h"

void place_order(int user_id, int restaurant_id, const std::vector<std::tuple<int, int>>& items) {
    double total_amount = 0.0;
    for (const auto& item : items) {
        int menu_item_id = std::get<0>(item);
        int quantity = std::get<1>(item);

        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT price FROM menu_items WHERE id=?"));
        pstmt->setInt(1, menu_item_id);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            double price = res->getDouble("price");
            total_amount += price * quantity;
        }
    }

    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO orders (user_id, restaurant_id, total_amount, status) VALUES (?, ?, ?, ?)"));
    pstmt->setInt(1, user_id);
    pstmt->setInt(2, restaurant_id);
    pstmt->setDouble(3, total_amount);
    pstmt->setString(4, "Pending");
    pstmt->execute();

    int order_id = pstmt->getUpdateCount();

    for (const auto& item : items) {
        int menu_item_id = std::get<0>(item);
        int quantity = std::get<1>(item);

        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO order_items (order_id, menu_item_id, quantity) VALUES (?, ?, ?)"));
        pstmt->setInt(1, order_id);
        pstmt->setInt(2, menu_item_id);
        pstmt->setInt(3, quantity);
        pstmt->execute();
    }
}

std::vector<std::tuple<int, int, int, double, std::string, std::string>> get_orders(int user_id) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM orders WHERE user_id=?"));
    pstmt->setInt(1, user_id);
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    std::vector<std::tuple<int, int, int, double, std::string, std::string>> orders;

    while (res->next()) {
        orders.emplace_back(res->getInt("id"), res->getInt("user_id"), res->getInt("restaurant_id"), res->getDouble("total_amount"), res->getString("status"), res->getString("created_at"));
    }
    return orders;
}

