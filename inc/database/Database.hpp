#pragma once

#include <string>
#include "sqlite/sqlite3.h"

class Database {
private:
    sqlite3* m_db;
    bool m_is_open;
    std::string m_path;
    static int callback(void* data, int argc, char** argv, char** azColName);
public:
    Database() = delete;
    ~Database();
    Database(std::string path);
    void close();
    void open();

    int exec(std::string sql);
    template<typename T>
    int exec(std::string sql, int(*callback)(void*, int, char**, char**), T* data);

};

template<typename T>
inline int Database::exec(std::string sql, int(*callback)(void*, int, char**, char**), T* data)
{

    char* zErrMsg = 0;
    int res = sqlite3_exec(m_db, sql.c_str(), callback, data, &zErrMsg);
    if (res != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        return 0;
    }
    else {
        return 1;
    }
}
