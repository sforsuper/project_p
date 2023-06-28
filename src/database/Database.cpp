#include <iostream>
#include "sqlite/sqlite3.h"
#include "database/Database.hpp"

Database::Database(std::string path) : m_path(path), m_is_open(false){}

void Database::close() {
    if(m_is_open == true)
        sqlite3_close(m_db);
}

void Database::open() {
    try
    {
        int rc = sqlite3_open("data.db", &m_db);
        if (rc != SQLITE_OK) {

        }
        else {
            m_is_open = true;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Database::exec(std::string sql) {

}

Database::~Database() {
    if(m_is_open == true)
        sqlite3_close(m_db);
}
