#pragma once

#include "LocalDataRepository.hpp"
#include "database/Database.hpp"

class LocalDataRepositoryImpl : public LocalDataRepository{
private:
    Database* m_database;



public:
    LocalDataRepositoryImpl();
    int insertStudent(Student student) override;
    int insertAdmin(Admin admin);
    int loginStudent(std::string login, std::string password) override;
    int loginAdmin(std::string login, std::string password) override;
    int insertActivity(Activity activity) override;
    std::string getUserActivities(int id) override;
    std::string getAdminActivities(int id) override;
    std::string getActivities() override;
    int updateUserActivities(int user_id, int activity_id) override;
    int updateAdminActivities(int user_id, int activity_id) override;


};
