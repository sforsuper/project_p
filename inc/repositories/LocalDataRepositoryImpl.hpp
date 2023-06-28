#pragma once

#include "LocalDataRepository.hpp"
#include "database/Database.hpp"

class LocalDataRepositoryImpl : public LocalDataRepository{
private:
    Database* m_database;
public:
    LocalDataRepositoryImpl();
    void insertStudent(Student student) override;

};
