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
            m_is_open = false;
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

int Database::callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int Database::exec(std::string sql) {
    char* zErrMsg = 0;
    int res = sqlite3_exec(m_db, sql.c_str(), callback, 0, &zErrMsg);
    if (res != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        return 0;
    }
    else {
        return 1;
    }
}

Database::~Database() {
    if(m_is_open == true)
        sqlite3_close(m_db);
}
