#include "db_connection.h"
#include <iostream>

sql::mysql::MySQL_Driver* driver;
std::shared_ptr<sql::Connection> conn;

void connect_db() {
    driver = sql::mysql::get_mysql_driver_instance();
    conn = std::shared_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306", "root", "password"));
    conn->setSchema("food_ordering_system");
    if (conn) {
        std::cout << "Database connected successfully!" << std::endl;
    } else {
        std::cout << "Failed to connect to database." << std::endl;
    }
}
