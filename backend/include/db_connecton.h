#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <memory>

void connect_db();
extern std::shared_ptr<sql::Connection> conn;

#endif // DB_CONNECTION_H
