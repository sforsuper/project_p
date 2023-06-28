#include "repositories/LocalDataRepositoryImpl.hpp"



LocalDataRepositoryImpl::LocalDataRepositoryImpl() {
    m_database = new Database("data.db");
}

void LocalDataRepositoryImpl::insertStudent(Student student) {
    std::string sql = std::string ("INSERT INTO users (user_name,user_surname,login,password,activities) ") +
                      "VALUES (" + "'" + student.name + "', '" + student.surname + "', '";
    m_database->exec(sql);
}
