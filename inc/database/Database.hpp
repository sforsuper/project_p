#pragma once

#include <string>
#include "sqlite/sqlite3.h"

class Database {
private:
    sqlite3* m_db;
    bool m_is_open;
    std::string m_path;

public:
    Database() = delete;
    ~Database();
    Database(std::string path);
    void close();
    void open();
    void exec(std::string sql);

};
