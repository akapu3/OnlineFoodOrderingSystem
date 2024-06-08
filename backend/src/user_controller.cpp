#include "user_controller.h"
#include "db_connection.h"

void register_user(const std::string& username, const std::string& password, const std::string& email) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO users (username, password, email) VALUES (?, ?, ?)"));
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    pstmt->setString(3, email);
    pstmt->execute();
}

bool login_user(const std::string& username, const std::string& password) {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM users WHERE username=? AND password=?"));
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    return res->next();
}
